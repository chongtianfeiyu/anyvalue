/*************************************************************************
	> File Name: encode.cpp
	> Author: jiangyouxing
	> Mail: 82776315@qq.com
	> Created Time: Thu 11 Dec 2014 05:08:53 PM SGT
 ************************************************************************/

#include "encode.h"

static bool IS_LIST(zval **val TSRMLS_DC)
{
    int i;
    HashTable *myht = HASH_OF(*val);

    i = myht ? zend_hash_num_elements(myht) : 0;
    if (i > 0)
    {
        char *key;
        ulong index, idx;
        uint key_len;
        HashPosition pos;

        zend_hash_internal_pointer_reset_ex(myht, &pos);
        idx = 0;
        for (;; zend_hash_move_forward_ex(myht, &pos))
        {
            i = zend_hash_get_current_key_ex(myht, &key, &key_len, &index, 0, &pos);
            if (i == 3)
            {
                break;
            }

            if (i == HASH_KEY_IS_STRING)
            {
                return false;
            }
            else
            {
                if (index != idx)
                {
                    return false;
                }
            }
            idx++;
        }
    }

    return true;
}


void encode(std::string &sBuf,zval *object)
{
    if (object->type == IS_BOOL)
    {
        encode_bool(sBuf, object);
    }
    else if (object->type == IS_NULL)
    {
        encode_none(sBuf,object);
    }
    else if (object->type == IS_STRING)
    {
        encode_string(sBuf,object);
    }
    else if (object->type == IS_DOUBLE)
    {
        encode_float(sBuf, object);
    }
    else if (object->type == IS_LONG)
    {
        encode_integer(sBuf, object);
    }
    else if (object->type == IS_ARRAY && IS_LIST(&object))
    {
        encode_list(sBuf,object);
    }
    else if (object->type == IS_ARRAY && !IS_LIST(&object))
    {
        encode_map(sBuf,object);
    }
    else
    {
        throw std::runtime_error("not a encodable object");
    }
}


void encode_integer(std::string& sBuf, zval *object )
{
    long long llValue = 0;

    llValue = object->value.lval;

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

void encode_bool(std::string& sBuf, zval *object)
{
    sBuf.push_back((char)DType::Bool);
    sBuf.push_back((char)object->value.lval);
}

void encode_float(std::string& sBuf, zval *object)
{
    double flValue = object->value.dval;
    sBuf.push_back((char)DType::Float);
    uint64_t ui64Tmp = *(uint64_t*)&flValue;
    uint64_t ui64Tmp2 = htonll(ui64Tmp);
    sBuf.append(reinterpret_cast<char*>(&ui64Tmp2),sizeof(ui64Tmp2));
}


void encode_string(std::string& sBuf,zval *object)
{
    char *data = NULL;
    size_t len = 0;

    data = object->value.str.val;
    len = object->value.str.len;

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

void encode_list(std::string& sBuf, zval *object)
{

    HashTable *myht;
    myht = HASH_OF(object);

    size_t size = zend_hash_num_elements(myht);
    sBuf.push_back((char)DType::Vector);
    uint32_t dwSize = htonl(static_cast<uint32_t>(size));
    sBuf.append(reinterpret_cast<char*>(&dwSize), sizeof(dwSize));

    char *key;
    zval **data;
    ulong index;
    uint key_len;
    HashPosition pos;
    HashTable *tmp_ht;
    int i = 0;
    zend_hash_internal_pointer_reset_ex(myht, &pos);
    for (;; zend_hash_move_forward_ex(myht, &pos))
    {
        i = zend_hash_get_current_key_ex(myht, &key, &key_len, &index, 0, &pos);
        if (i == 3)
            break;
        if (zend_hash_get_current_data_ex(myht, (void **) &data, &pos) == SUCCESS)
        {
            encode(sBuf,*data);
        }
    }
}

void encode_map(std::string& sBuf, zval *object)
{

    HashTable *myht;
    myht = HASH_OF(object);
    size_t size = zend_hash_num_elements(myht);
    sBuf.push_back((char)DType::Map);
    size_t dwSizePos = sBuf.size();
    uint32_t dwSize = 0;//htonl(_cast<unsigned long>(value.map->size()));
    sBuf.append(reinterpret_cast<char*>(&dwSize), sizeof(dwSize));

    char *key;
    zval **data;
    ulong index;
    uint key_len;
    HashPosition pos;
    HashTable *tmp_ht;
    int i = 0;
    zend_hash_internal_pointer_reset_ex(myht, &pos);

    for (;; zend_hash_move_forward_ex(myht, &pos))
    {
        i = zend_hash_get_current_key_ex(myht, &key, &key_len, &index, 0, &pos);
        if (i == 3)
            break;

        if(i == HASH_KEY_IS_STRING)
        {
            sBuf.push_back((char)key_len-1);
            sBuf.append(key,(size_t)key_len-1);
        }
        else
        {
            char szData[20];
            snprintf(szData,sizeof(szData),"%d",(int)index);
            sBuf.push_back((char)strlen(szData));
            sBuf.append(szData);
        }

        if (zend_hash_get_current_data_ex(myht, (void **) &data, &pos) == SUCCESS)
        {
            ++dwSize;
            encode(sBuf,*data);
        }
    }
    dwSize = htonl(dwSize);
    memcpy((char*)sBuf.data()+dwSizePos, reinterpret_cast<char*>(&dwSize), sizeof(dwSize));
}


void encode_none(std::string& sBuf, zval *object)
{
    sBuf.push_back((char)DType::Null);
}
