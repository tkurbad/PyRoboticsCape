/*
 * roboticscape.c - Python bindings for Strawson Design's libroboticscape
 * Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
 *
 */

#include <Python.h>
#include <roboticscape.h>

static PyObject *rcInitialize(PyObject *self, PyObject *args);
static PyObject *rcCleanup(PyObject *self, PyObject *args);

static PyObject *rcGetState(PyObject *self, PyObject *args);
static PyObject *rcPrintState(PyObject *self, PyObject *args);

static PyObject *rcGetEncoderPos(PyObject *self, PyObject *args);

static PyObject *rcBatteryVoltage(PyObject *self, PyObject *args);
static PyObject *rcDCJackVoltage(PyObject *self, PyObject *args);

static PyMethodDef RoboticsCapeMethods[] = {
    {"rcInitialize", rcInitialize, METH_O,
        "Initialize RoboticsCape hard- and software."},
    {"rcCleanup", rcCleanup, METH_O,
        "Shut down RoboticsCape library and functions."},
    {"rcGetState", rcGetState, METH_O,
        "Get high level robot state."},
    {"rcPrintState", rcPrintState, METH_O,
        "Print textual representation of high level robot state."},
    {"rcGetEncoderPos", rcGetEncoderPos, METH_VARARGS,
        "Get quadrature encoder position for given channel or for all channels."},
    {"rcBatteryVoltage", rcBatteryVoltage, METH_O,
        "Get LiPo battery voltage."},
    {"rcDCJackVoltage", rcDCJackVoltage, METH_O,
        "Get DC jack voltage."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef RoboticsCapeModule = {
    PyModuleDef_HEAD_INIT,
    "RoboticsCape",         /* m_name */
                            /* m_doc */
    "This module defines the Python bindings for libroboticscape.\n"
    "libroboticscape is a collection of methods to interact with the\n"
    "BeagleBone Robotics Cape by Strawson Design or the BeagleBone Blue.\n",
    -1,                     /* m_size */
    RoboticsCapeMethods,    /* m_methods */
    NULL,                   /* m_reload */
    NULL,                   /* m_traverse */
    NULL,                   /* m_clear */
    NULL,                   /* m_free */
};
