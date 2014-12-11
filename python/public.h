#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#include "stdlib.h"

#if __BYTE_ORDER == __BIG_ENDIAN
#define ntohll(x)       (x)
#define htonll(x)       (x)
#else
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define ntohll(x)     __bswap_64 (x)
#define htonll(x)     __bswap_64 (x)
#endif
#endif

#define MAX_VALUE_TYPE = 17

struct DType
{
    enum ValueType	//realtype
    {
        Integer1	= 0,		///< tiny unint value (1字节)
        Integer2	= 1,		///< small unint value (2字节)
        Integer4	= 2,		///< unsigned integer value(int32)(4字节)
        Integer8	= 3,		///< big unsigned interger value(int64)(8字节)
        Integer		= Integer8,
        String1		= 4,		///< string value	//1个字节表示长度
        String2		= 5,		///< string value	//2个字节表示长度
        String4		= 6,		///< string value	//4个字节表示长度
        String		= String4,
        Vector		= 7,		///< array value (double list)
        Map			= 8,		///< object value (collection of name/value pairs).
        EXT			= 9,			/// customer
        Float       = 10,       /// float
        Bool        = 11,       ///bool
        Null        = 12,        ///null
        SInteger1	= 13,		///< tiny int value (1字节)
        SInteger2	= 14,		///< small int value (2字节)
        SInteger4	= 15,		///< signed integer value(int32)(4字节)
        SInteger8	= 16,		///< signed integer value(int64)(8字节)
        SInteger    = SInteger8,
    };
};

#endif
