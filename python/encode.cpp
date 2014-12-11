#include "encode.h"

void encode(std::string &sBuf,PyObject *object)
{
    if (object == Py_True || object == Py_False)
    {
        encode_bool(sBuf, object);
    }
    else if (object == Py_None)
    {
        encode_none(sBuf,object);
    }
    else if (PyString_Check(object))
    {
        encode_string(sBuf,object);
    }
    else if (PyUnicode_Check(object))
    {
        encode_unicode(sBuf,object);
    }
    else if (PyFloat_Check(object))
    {
        encode_float(sBuf, object);
    }
    else if (PyInt_Check(object) || PyLong_Check(object))
    {
        encode_integer(sBuf, object);
    }
    else if (PyList_Check(object))
    {
        encode_list(sBuf,object);
    }
    else if (PyTuple_Check(object))
    {
        encode_tuple(sBuf,object);
    }
    else if (PyDict_Check(object))     // use PyMapping_Check(object) instead? -Dan
    {
        encode_map(sBuf,object);
    }
    else
    {
        throw std::runtime_error("not a encodable object");
    }
}


void encode_integer(std::string& sBuf, PyObject * object )
{
    long long llValue = 0;
    if(PyInt_Check(object))
    {
        llValue = PyInt_AsLong(object);
    }
    else
    {
        llValue = PyLong_AsLongLong(object);
    }

    if(llValue >= 0)
    {
        if ( llValue < 0xFF )
        {
            sBuf.push_back((char)DType::Integer1);
            sBuf.push_back((char)llValue);
        }
        else if ( llValue <= 0xFFFF )
        {
            sBuf.push_back((char)DType::Integer2);
            unsigned short wTmp = htons(static_cast<unsigned short>(llValue));
            sBuf.append(reinterpret_cast<char*>(&wTmp),sizeof(wTmp));
        }
        else if ( llValue <= 0xFFFFFFFF )
        {
            sBuf.push_back((char)DType::Integer4);
            uint32_t dwTmp = htonl(static_cast<uint32_t>(llValue));
            sBuf.append(reinterpret_cast<char*>(&dwTmp),sizeof(dwTmp));
        }
        else
        {
            sBuf.push_back((char)DType::Integer8);
            uint64_t ui64Tmp = htonll(llValue);
            sBuf.append(reinterpret_cast<char*>(&ui64Tmp),sizeof(ui64Tmp));
        }
    }
    else
    {
        if(llValue > -129)
        {
            sBuf.push_back((char)DType::SInteger1);
            sBuf.push_back((char)llValue);
        }
        else if(llValue > -32769)
        {
            sBuf.push_back((char)DType::SInteger2);
            unsigned short wTmp = htons(static_cast<uint16_t>(llValue));
            sBuf.append(reinterpret_cast<char*>(&wTmp),sizeof(wTmp));
        }
        else if(llValue > -2147483649)
        {
            sBuf.push_back((char)DType::SInteger4);
            uint32_t dwTmp = htonl(static_cast<uint32_t>(llValue));
            sBuf.append(reinterpret_cast<char*>(&dwTmp),sizeof(dwTmp));
        }
        else
        {
            sBuf.push_back((char)DType::SInteger8);
            uint64_t ui64Tmp = htonll(llValue);
            sBuf.append(reinterpret_cast<char*>(&ui64Tmp),sizeof(ui64Tmp));
        }
    }
}

void encode_bool(std::string& sBuf, PyObject * object)
{
    sBuf.push_back((char)DType::Bool);

    if (object == Py_True || object == Py_False)
    {
        sBuf.push_back((char)1);
    }
    else
    {
        sBuf.push_back((char)0);
    }

}

void encode_float(std::string& sBuf, PyObject * object)
{
    double flValue = PyFloat_AsDouble(object);
    sBuf.push_back((char)DType::Float);
    uint64_t ui64Tmp = *(uint64_t*)&flValue;
    uint64_t ui64Tmp2 = htonll(ui64Tmp);
    sBuf.append(reinterpret_cast<char*>(&ui64Tmp2),sizeof(ui64Tmp2));
}


void encode_string(std::string& sBuf,PyObject * object)
{
    char *data = NULL;
    Py_ssize_t len = 0;
    PyString_AsStringAndSize(object,&data,&len);


    if ( len <= 0xFF )
    {
        sBuf.push_back((char)DType::String1);
        sBuf += static_cast<char>(len);
    }
    else if ( len <= 0xFFFF )
    {
        sBuf.push_back((char)DType::String2);
        unsigned short wSize = htons(static_cast<unsigned short>(len));
        sBuf.append(reinterpret_cast<char*>(&wSize), sizeof(wSize));
    }
    else
    {
        sBuf.push_back((char)DType::String4);
        uint32_t dwSize = htonl(static_cast<uint32_t>(len));
        sBuf.append(reinterpret_cast<char*>(&dwSize), sizeof(dwSize));
    }
    sBuf.append(data,len);
}

void encode_unicode(std::string& sBuf,PyObject * object)
{
    PyObject* pObj = PyUnicode_AsUTF8String(object);
    encode_string(sBuf,pObj);
    Py_XDECREF(pObj);
}


void encode_list(std::string& sBuf, PyObject * object)
{
    Py_ssize_t size = PyList_Size(object);
    sBuf.push_back((char)DType::Vector);
    uint32_t dwSize = htonl(static_cast<uint32_t>(size));
    sBuf.append(reinterpret_cast<char*>(&dwSize), sizeof(dwSize));
    for(Py_ssize_t i=0;i<size;i++)
    {
        encode(sBuf,PyList_GetItem(object,i));
    }
}

void encode_tuple(std::string& sBuf, PyObject * object)
{
    Py_ssize_t size = PyTuple_Size(object);
    sBuf.push_back((char)DType::Vector);
    uint32_t dwSize = htonl(static_cast<uint32_t>(size));
    sBuf.append(reinterpret_cast<char*>(&dwSize), sizeof(dwSize));
    for(Py_ssize_t i=0;i<size;i++)
    {
        encode(sBuf,PyTuple_GetItem(object,i));
    }
}

void encode_map(std::string& sBuf, PyObject * object)
{
    Py_ssize_t size = PyDict_Size(object);

    sBuf.push_back((char)DType::Map);
    size_t dwSizePos = sBuf.size();
    uint32_t dwSize = 0;//htonl(_cast<unsigned long>(value.map->size()));
    sBuf.append(reinterpret_cast<char*>(&dwSize), sizeof(dwSize));


    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(object, &pos, &key, &value))
    {
        if(!PyString_Check(key))
            continue;
        ++dwSize;
        char *keydata = NULL;
        Py_ssize_t len = 0;
        PyString_AsStringAndSize(key,&keydata,&len);
        sBuf.push_back((char)len);
        sBuf.append(keydata,(size_t)len);
        encode(sBuf,value);
    }

    dwSize = htonl(dwSize);
    memcpy((char*)sBuf.data()+dwSizePos, reinterpret_cast<char*>(&dwSize), sizeof(dwSize));

}


void encode_none(std::string& sBuf, PyObject * object)
{
    sBuf.push_back((char)DType::Null);
}
