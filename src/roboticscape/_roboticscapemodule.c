/*
 * roboticscapemodule.c - Python bindings for Strawson Design's
 * libroboticscape
 * 
 * Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
 *
 */

#include <Python.h>
#include "_roboticscapemodule.h"

static PyObject *rcInitialize(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_initialize();

    return Py_BuildValue("i", retval);
}

static PyObject *rcCleanup(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_cleanup();

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetState(PyObject *self, PyObject *args) {
    int state;

    state = (int)rc_get_state();

    return Py_BuildValue("i", state);
}

static PyObject *rcSetState(PyObject *self, PyObject *args) {
    int state;
    int retval;

    if (!PyArg_ParseTuple(args, "i", &state)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (state to set) required.");
        PyErr_Print();
    }

    if ((state < 0) || (state > 3)) {
        PyErr_SetString(PyExc_ValueError, "State has to be >= 0 and <= 3.");
        PyErr_Print();
    }

    retval = rc_set_state(state);

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetEncoderPos(PyObject *self, PyObject *args) {
    long position;
    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (encoder channel number) required.");
        PyErr_Print();
    }

    if ((channel < 1) || (channel > 4)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 4.");
        PyErr_Print();
    }

    position = (long)rc_get_encoder_pos(channel);

    return Py_BuildValue("l", position);
}

static PyObject *rcBatteryVoltage(PyObject *self, PyObject *args) {
    float voltage;

    voltage = rc_battery_voltage();

    return Py_BuildValue("f", voltage);
}

static PyObject *rcDCJackVoltage(PyObject *self, PyObject *args) {
    float voltage;

    voltage = rc_dc_jack_voltage();

    return Py_BuildValue("f", voltage);
}

PyMODINIT_FUNC
PyInit__roboticscape(void)
{
	PyObject* m;

	m = PyModule_Create(&RoboticsCapeModule);

    if (m == NULL)
        return NULL;

	return m;
}
