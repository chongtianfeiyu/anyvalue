#ifndef __DECODE_H__
#define __DECODE_H__
#include "public.h"
#include <python2.7/Python.h>
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


typedef PyObject *  (*DECODE_FUNC)(size_t& , const char* , const size_t);
void check(const size_t dwPos, const size_t sDataSize);
PyObject * decode(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_bool(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_integer1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_integer2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_integer4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_integer8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_sinteger1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_sinteger2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_sinteger4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_sinteger8(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_string1(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_string2(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_string4(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_vector(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_map(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_null(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_ext(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);
PyObject * decode_float(size_t& dwDecodePos, const char* pData, const size_t dwDataSize);


#endif
