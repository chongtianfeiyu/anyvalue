#include "decode.h"

//extern PyObject *AnyValueError;

PyObject * decode(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    static DECODE_FUNC arDecodeFunc[17] = {&decode_integer1, &decode_integer2, &decode_integer4, &decode_integer8,&decode_string1,
                                               &decode_string2, &decode_string4, &decode_vector, &decode_map,  &decode_ext, &decode_float,&decode_bool,&decode_null,
                                               &decode_sinteger1,&decode_sinteger2,&decode_sinteger4,&decode_sinteger8
                                              };
    check(dwDecodePos+1, dwDataSize);
    uint8_t ucSubType = *(pData+dwDecodePos);
    dwDecodePos++;

    if ( ucSubType< 17 )
    {
        return arDecodeFunc[ucSubType](dwDecodePos, pData, dwDataSize);
    }

    return NULL;
}

void  check(const size_t dwPos, const size_t sDataSize)
{
    if ( dwPos >  sDataSize )
    {
        throw std::runtime_error("check size fail");
    }
}

PyObject *  decode_bool(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+1, dwDataSize);
    pObject = PyBool_FromLong((unsigned char)*(unsigned char*)(pData+dwDecodePos));
    ++dwDecodePos;
    return pObject;
}

PyObject *  decode_integer1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+1, dwDataSize);
    pObject = PyInt_FromLong((unsigned char)*(unsigned char*)(pData+dwDecodePos));
    ++dwDecodePos;
    return pObject;

}
PyObject *  decode_integer2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+2, dwDataSize);
    pObject = PyInt_FromLong(ntohs(*(unsigned short*)(pData+dwDecodePos)));
    dwDecodePos += 2;
    return pObject;
}
PyObject *  decode_integer4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+4, dwDataSize);
    pObject = PyInt_FromLong(ntohl(*(uint32_t*)(pData+dwDecodePos)));
    dwDecodePos += 4;
    return pObject;
}
PyObject *  decode_integer8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+8, dwDataSize);
    pObject = PyInt_FromLong(ntohll(*(uint64_t*)(pData+dwDecodePos)));
    dwDecodePos += 8;
    return pObject;
}

PyObject * decode_sinteger1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+1, dwDataSize);
    pObject = PyInt_FromLong(*(char*)(pData+dwDecodePos));
    ++dwDecodePos;

    return pObject;

}
PyObject * decode_sinteger2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+2, dwDataSize);
    pObject = PyInt_FromLong((int16_t)ntohs(*(unsigned short*)(pData+dwDecodePos)));
    dwDecodePos += 2;
    return pObject;
}
PyObject * decode_sinteger4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+4, dwDataSize);
    pObject = PyInt_FromLong((int32_t)ntohl(*(uint32_t*)(pData+dwDecodePos)));
    dwDecodePos += 4;
    return pObject;
}
PyObject * decode_sinteger8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+8, dwDataSize);
    pObject = PyInt_FromLong((int64_t) ntohll(*(uint64_t*)(pData+dwDecodePos)));
    dwDecodePos += 8;
    return pObject;
}

PyObject *  decode_string1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{

    PyObject *pObject;
    check(dwDecodePos+1, dwDataSize);
    unsigned char ucStrLen = *(unsigned char*)(pData+dwDecodePos);
    ++dwDecodePos;
    check(dwDecodePos+ucStrLen, dwDataSize);

    pObject = PyString_FromStringAndSize(pData+dwDecodePos, ucStrLen);
    dwDecodePos += ucStrLen;
    return pObject;
}
PyObject *  decode_string2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+2, dwDataSize);
    unsigned short wStrLen = ntohs(*(unsigned short*)(pData+dwDecodePos));
    dwDecodePos += 2;
    check(dwDecodePos+wStrLen, dwDataSize);
    pObject = PyString_FromStringAndSize(pData+dwDecodePos, wStrLen);
    dwDecodePos += wStrLen;
    return pObject;
}
PyObject *  decode_string4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    check(dwDecodePos+4, dwDataSize);
    uint32_t dwStrLen = ntohl(*(uint32_t*)(pData+dwDecodePos));
    dwDecodePos += 4;
    check(dwDecodePos+dwStrLen, dwDataSize);
    pObject = PyString_FromStringAndSize(pData+dwDecodePos, dwStrLen);
    dwDecodePos += dwStrLen;
    return pObject;
}
PyObject *  decode_vector(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    pObject = PyList_New(0);

    check(dwDecodePos+4, dwDataSize);
    uint32_t dwSize = ntohl(*(uint32_t*)(pData+dwDecodePos));
    dwDecodePos += 4;
    while ( dwSize > 0 )
    {

        --dwSize;
        PyObject *item;
        item = decode(dwDecodePos, pData, dwDataSize);
        PyList_Append(pObject,item);
        Py_XDECREF(item);

    }
    return pObject;
}
PyObject *  decode_map(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    pObject = PyDict_New();

    check(dwDecodePos+4, dwDataSize);
    uint32_t dwSize = ntohl(*(uint32_t*)(pData+dwDecodePos));
    dwDecodePos += 4;
    while ( dwSize > 0 )
    {
        --dwSize;
        check(dwDecodePos+1, dwDataSize);
        unsigned char ucNameLen =  *(unsigned char*)(pData+dwDecodePos);
        ++dwDecodePos;
        check(dwDecodePos+ucNameLen, dwDataSize);

        PyObject *pKey = PyString_FromStringAndSize(pData+dwDecodePos, ucNameLen);
        dwDecodePos += ucNameLen;

        if ( dwDataSize > dwDecodePos )
        {
            PyObject *item;
            item = decode(dwDecodePos, pData, dwDataSize);
            PyDict_SetItem(pObject,pKey,item);
            Py_XDECREF(item);

        }
        Py_XDECREF(pKey);
    }
    return pObject;
}

PyObject *  decode_null(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject = Py_None;
    Py_XINCREF(pObject);
    return pObject;
}
PyObject *  decode_ext(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{

}
PyObject *  decode_float(size_t& dwDecodePos, const char* pData, const size_t dwDataSize)
{
    PyObject *pObject;
    double flValue;
    check(dwDecodePos+8, dwDataSize);
    uint64_t ui64Tmp = ntohll(*(uint64_t*)(pData+dwDecodePos));
    flValue =*(double*)&ui64Tmp;
    dwDecodePos += 8;
    pObject=PyFloat_FromDouble(flValue);
    return pObject;
}
