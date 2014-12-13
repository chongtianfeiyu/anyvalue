/*************************************************************************
	> File Name: encode.h
	> Author: jiangyouxing
	> Mail: 82776315@qq.com
	> Created Time: Thu 11 Dec 2014 05:09:03 PM SGT
 ************************************************************************/

#ifndef __ENCODE_H__
#define __ENCODE_H__
#include "public.h"
#include <php.h>
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

void encode(std::string &sBuf,zval *object);
inline void encode_bool(std::string &sBuf,zval *object);
inline void encode_none(std::string &sBuf,zval *object);
inline void encode_float(std::string &sBuf,zval *object);
inline void encode_integer(std::string &sBuf,zval *object);
inline void encode_string(std::string &sBuf,zval *object);
inline void encode_list(std::string &sBuf,zval *object);
inline void encode_map(std::string &sBuf,zval *object);


#endif
