/*************************************************************************
	> File Name: anyvalue.cpp
	> Author: jiangyouxing
	> Mail: 82776315@qq.com
	> Created Time: Thu 11 Dec 2014 05:09:23 PM SGT
 ************************************************************************/


#include "php.h"
#include "decode.h"
#include "encode.h"

using namespace std;

/* declaration of functions to be exported */
ZEND_FUNCTION(av_encode);
ZEND_FUNCTION(av_decode);

/* compiled function list so Zend knows what's in this module */
zend_function_entry anyvalue_functions[] =
{
    ZEND_FE(av_encode, NULL)
    ZEND_FE(av_decode, NULL)
    {NULL, NULL, NULL}
};

/* compiled module information */
zend_module_entry anyvalue_module_entry =
{
    STANDARD_MODULE_HEADER,
    "AnyValue Module",
    anyvalue_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NO_VERSION_YET,
    STANDARD_MODULE_PROPERTIES
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#if COMPILE_DL_FIRST_MODULE
    ZEND_GET_MODULE(anyvalue)
#endif

/* implement function that is meant to be made available to PHP */
ZEND_FUNCTION(av_encode)
{
    zval * value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &value)== FAILURE)
    {
        zend_error(E_WARNING,"%s","param invalid");
        return;
    }

    string sBuf;
    try
    {
        encode(sBuf,value);
    }
    catch(const exception &e)
    {
        zend_error(E_WARNING,"%s",e.what());
    }

    ZVAL_STRINGL(return_value,sBuf.data(),sBuf.size(),1);

}


ZEND_FUNCTION(av_decode)
{
    char *data = NULL;;
    size_t len = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &data,&len)== FAILURE)
    {
        zend_error(E_WARNING,"%s","param must be string");
        return;
    }

    size_t pos = 0;
    try
    {
        decode(pos,data,len,return_value);
    }
    catch(const exception &e)
    {
        zend_error(E_WARNING,"%s",e.what());
    }
}
