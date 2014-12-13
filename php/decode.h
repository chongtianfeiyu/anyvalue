/*************************************************************************
	> File Name: decode.h
	> Author: jiangyouxing
	> Mail: 82776315@qq.com
	> Created Time: Thu 11 Dec 2014 05:09:12 PM SGT
 ************************************************************************/

#ifndef __DECODE_H__
#define __DECODE_H__
#include "php.h"
#include "public.h"
#include <stdexcept>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <memory.h>
#include <assert.h>
#include <iostream>
#include <deque>
#include <stdint.h>
#include <netinet/in.h>
#include <math.h>


typedef void  (*DECODE_FUNC)(size_t& , const char* , const size_t,zval *);
void decode(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);

inline void check(const size_t dwPos, const size_t sDataSize);
inline void decode_bool(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_integer1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_integer2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_integer4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_integer8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_sinteger1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_sinteger2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_sinteger4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_sinteger8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_string1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_string2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_string4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_vector(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_map(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_null(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_ext(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);
inline void decode_float(size_t& dwDecodePos, const char* pData, const size_t dwDataSize,zval *zvalue);


#endif

