/*
 * roboticscape.c - Python bindings for Strawson Design's libroboticscape
 * Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
 *
 */

#include <Python.h>
#include "roboticscapemodule.h"

static PyObject *rcGetEncoderPos(PyObject *self, PyObject *args) {
    long position = 0;
    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel))
        return Py_BuildValue("l", position);

    position = (long)rc_get_encoder_pos(channel);

    return Py_BuildValue("l", position);
}

PyMODINIT_FUNC
PyInit_roboticscape(void)
{
	PyObject* m;

	m = PyModule_Create(&RoboticsCapeModule);

    if (m == NULL)
        return NULL;

	return m;
}
