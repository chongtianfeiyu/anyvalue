#include <Python.h>
#include "decode.h"
#include "encode.h"
using namespace std;


extern "C"
{
    PyObject *AnyValueError;
    static PyObject *decode(PyObject * self, PyObject *args);
    static PyObject *decode(PyObject * self, PyObject *args);

    static PyObject *decode(PyObject *self, PyObject *args)
    {

        PyObject * pString;

        char *pData = NULL;
        uint32_t dwDataSize = 0;
        size_t dwDecodePos = 0;

        if (!PyArg_ParseTuple(args, "S",&pString))
           return NULL;

        pData = PyString_AS_STRING(pString);
        dwDataSize = PyString_GET_SIZE(pString);

        if ( dwDataSize < 1 )
        {
            return NULL;
        }

        try
        {
            return  decode(dwDecodePos,pData, dwDataSize);
        }
        catch(const exception &e)
        {
            PyErr_SetString(AnyValueError,e.what());
            return NULL;
        }

    }

    static PyObject *encode(PyObject *self, PyObject *args)
    {
        PyObject * obj;
        if (!PyArg_ParseTuple(args, "O", &obj))
           return NULL;
        std::string sBuf;
        try
        {
            encode(sBuf,obj);
            return PyString_FromStringAndSize(sBuf.data(),sBuf.size());
        }
        catch(const std::exception &e)
        {
            PyErr_SetString(AnyValueError,e.what());
            return NULL;
        }

    }

    static PyMethodDef FooMethods[] = {
        {"decode",  decode, METH_VARARGS},
        {"encode",  encode, METH_VARARGS},
        {NULL, NULL}
    };

    PyObject *  initanyvalue()
    {
        PyObject *module = (PyObject * ) Py_InitModule("anyvalue", FooMethods);
        if(module == NULL)
        {
            return NULL;
        }
        AnyValueError = PyErr_NewException((char*)"anyvalue.error",NULL,NULL);
        Py_INCREF(AnyValueError);
        PyModule_AddObject(module,"error",AnyValueError);
    }



}
