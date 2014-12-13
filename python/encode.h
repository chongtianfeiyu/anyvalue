#ifndef __ENCODE_H__
#define __ENCODE_H__
#include "public.h"
#include <Python.h>
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

void encode(std::string &sBuf,PyObject *object);
void encode_bool(std::string &sBuf,PyObject *object);
void encode_none(std::string &sBuf,PyObject *object);
void encode_float(std::string &sBuf,PyObject *object);
void encode_integer(std::string &sBuf,PyObject *object);
void encode_string(std::string &sBuf,PyObject *object);
void encode_unicode(std::string &sBuf,PyObject *object);
void encode_list(std::string &sBuf,PyObject *object);
void encode_tuple(std::string &sBuf,PyObject *object);
void encode_map(std::string &sBuf,PyObject *object);


#endif
