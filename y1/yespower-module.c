#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "yespower.h"

#define OUTPUT_SIZE 	44
static PyObject *foo(PyObject *self, PyObject *args)
{
	void *output;
	unsigned int out_no, ref;
	int ret;
	PyObject *value;
	PyBytesObject *input;
	if (!PyArg_ParseTuple(args, "SII", &input, &out_no, &ref))
		return NULL;
	Py_INCREF(input);
	output = PyMem_Malloc(OUTPUT_SIZE);
	ret = y1_foo((void *)PyBytes_AsString((PyObject*) input), output, &out_no, ref);
	Py_DECREF(input);
	value = Py_BuildValue("y#Ii", output, OUTPUT_SIZE, out_no, ret);
	PyMem_Free(output);
	return value;
}

/*
static PyObject *foo2(PyObject *self, PyObject *args)
{
	char *output;
	unsigned int out_mask;
	unsigned int out_no;
	int ret;
	PyObject *value;
	PyBytesObject *input;
	if (!PyArg_ParseTuple(args, "SII", &input, &out_no, &out_mask))
		return NULL;
	Py_INCREF(input);
	output = PyMem_Malloc(32);
	ret = y1_foo2((char *)PyBytes_AsString((PyObject*) input), output, &out_no, &out_mask);
	Py_DECREF(input);
	value = Py_BuildValue("y#IIi", output, 32, out_no, out_mask, ret);

	PyMem_Free(output);
	return value;
}

static PyObject *b1_foo(PyObject *self, PyObject *args)
{
	char *output;
	PyObject *value;
	PyBytesObject *input;
	if (!PyArg_ParseTuple(args, "S", &input))
		return NULL;
	Py_INCREF(input);
	output = PyMem_Malloc(32);
	_b1_foo((char *)PyBytes_AsString((PyObject*) input), output);
	Py_DECREF(input);
	value = Py_BuildValue("y#", output, 32);

	PyMem_Free(output);
	return value;
}

static PyObject *b1_foo2(PyObject *self, PyObject *args)
{
	void *output;
	unsigned int out_mask;
	unsigned int out_no;
	int ret;
	PyObject *value;
	PyBytesObject *input;
	if (!PyArg_ParseTuple(args, "SII", &input, &out_no, &out_mask))
		return NULL;
	Py_INCREF(input);
	output = PyMem_Malloc(32);
	ret = _b1_foo2((void *)PyBytes_AsString((PyObject*) input), output, &out_no, &out_mask);
	Py_DECREF(input);
	value = Py_BuildValue("y#IIi", output, 32, out_no, out_mask, ret);

	PyMem_Free(output);
	return value;
}
*/

static PyMethodDef y1Methods[] = {
	{ "foo", foo, METH_VARARGS, "" },
	//{ "foo2", foo2, METH_VARARGS, "" },
	//{ "b1_foo", b1_foo, METH_VARARGS, "" },
	//{ "b1_foo2", b1_foo2, METH_VARARGS, "" },
	{ NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef y1Module = {
	PyModuleDef_HEAD_INIT,
	"y1",
	"...",
	-1,
	y1Methods
};

PyMODINIT_FUNC PyInit_y1(void) {
	return PyModule_Create(&y1Module);
}

#else

PyMODINIT_FUNC inity1(void) {
	(void) Py_InitModule("y1", y1Methods);
}
#endif
