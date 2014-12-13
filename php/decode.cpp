/*************************************************************************
	> File Name: decode.cpp
	> Author: jiangyouxing
	> Mail: 82776315@qq.com
	> Created Time: Thu 11 Dec 2014 05:08:42 PM SGT
 ************************************************************************/
#include "decode.h"

void check(const size_t dwPos, const size_t sDataSize)
{
    if ( dwPos >  sDataSize )
    {
        throw std::runtime_error("decode data check pos fail.");
    }
}

void decode(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue)
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
        arDecodeFunc[ucSubType](dwDecodePos, pData, dwDataSize, zvalue);
    }
}


void decode_bool(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+1, dwDataSize);
    unsigned char value = (unsigned char)*(unsigned char*)(pData+dwDecodePos);
    if(value == 1)
    {
        ZVAL_BOOL(zvalue,true);
    }
    else
    {
        ZVAL_BOOL(zvalue,false);
    }
    ++dwDecodePos;

}

void decode_integer1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+1, dwDataSize);
    ZVAL_LONG(zvalue,(unsigned char)*(unsigned char*)(pData+dwDecodePos));
    ++dwDecodePos;

}
void decode_integer2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+2, dwDataSize);
    ZVAL_LONG(zvalue,ntohs(*(unsigned short*)(pData+dwDecodePos)));
    dwDecodePos += 2;
}
void decode_integer4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+4, dwDataSize);
    ZVAL_LONG(zvalue,ntohl(*(uint32_t*)(pData+dwDecodePos)));
    dwDecodePos += 4;
}
void decode_integer8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+8, dwDataSize);
    ZVAL_LONG(zvalue,ntohll(*(uint64_t*)(pData+dwDecodePos)));
    dwDecodePos += 8;
}


void decode_sinteger1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+1, dwDataSize);
    ZVAL_LONG(zvalue,*(char*)(pData+dwDecodePos));
    ++dwDecodePos;

}
void decode_sinteger2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+2, dwDataSize);
    ZVAL_LONG(zvalue,(int16_t)ntohs(*(uint16_t*)(pData+dwDecodePos)));
    dwDecodePos += 2;
}
void decode_sinteger4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+4, dwDataSize);
    ZVAL_LONG(zvalue,(int32_t)ntohl(*(uint32_t*)(pData+dwDecodePos)));
    dwDecodePos += 4;
}
void decode_sinteger8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+8, dwDataSize);
    ZVAL_LONG(zvalue,(int64_t) ntohll(*(uint64_t*)(pData+dwDecodePos)));
    dwDecodePos += 8;
}

void decode_string1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+1, dwDataSize);
    unsigned char ucStrLen = *(unsigned char*)(pData+dwDecodePos);
    ++dwDecodePos;
    check(dwDecodePos+ucStrLen, dwDataSize);
    ZVAL_STRINGL(zvalue,pData+dwDecodePos, ucStrLen,true);
    dwDecodePos += ucStrLen;
}
void decode_string2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+2, dwDataSize);
    unsigned short wStrLen = ntohs(*(unsigned short*)(pData+dwDecodePos));
    dwDecodePos += 2;
    check(dwDecodePos+wStrLen, dwDataSize);
    ZVAL_STRINGL(zvalue,pData+dwDecodePos, wStrLen,true);
    dwDecodePos += wStrLen;
}
void decode_string4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+4, dwDataSize);
    uint32_t dwStrLen = ntohl(*(uint32_t*)(pData+dwDecodePos));
    dwDecodePos += 4;
    check(dwDecodePos+dwStrLen, dwDataSize);
    ZVAL_STRINGL(zvalue,pData+dwDecodePos, dwStrLen,true);
    dwDecodePos += dwStrLen;
}
void decode_vector(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    array_init(zvalue);
    check(dwDecodePos+4, dwDataSize);
    uint32_t dwSize = ntohl(*(uint32_t*)(pData+dwDecodePos));
    dwDecodePos += 4;
    while ( dwSize > 0 )
    {
        --dwSize;
        zval *value;
        MAKE_STD_ZVAL(value);
        add_next_index_zval(zvalue, value);
        decode(dwDecodePos, pData, dwDataSize,value);
    }
}
void decode_map(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    array_init(zvalue);
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

        std::string sKey(pData+dwDecodePos, ucNameLen);
        //sKey.assign();

        zval *value;
        MAKE_STD_ZVAL(value);

        add_assoc_zval(zvalue,sKey.c_str(),value);

        dwDecodePos += ucNameLen;
        if ( dwDataSize > dwDecodePos )
        {
            decode(dwDecodePos, pData, dwDataSize,value);
        }
    }
}

void decode_null(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    ZVAL_NULL(zvalue);
}
void decode_ext(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{

}
void decode_float(size_t& dwDecodePos, const char* pData, const size_t dwDataSize, zval *zvalue)
{
    check(dwDecodePos+8, dwDataSize);
    uint64_t ui64Tmp = ntohll(*(uint64_t*)(pData+dwDecodePos));
    ZVAL_DOUBLE(zvalue,*(double*)&ui64Tmp;)
    dwDecodePos += 8;
}
