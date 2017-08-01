/*
 * roboticscape.c - Python bindings for Strawson Design's libroboticscape
 * Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
 *
 */

#include <Python.h>
#include <roboticscape.h>

static PyObject *rcInitialize(PyObject *self);
static PyObject *rcCleanup(PyObject *self);

static PyObject *rcGetState(PyObject *self);
static PyObject *rcPrintState(PyObject *self);

static PyObject *rcGetEncoderPos(PyObject *self, PyObject *args);

static PyObject *rcBatteryVoltage(PyObject *self);
static PyObject *rcDCJackVoltage(PyObject *self);

static PyMethodDef RoboticsCapeMethods[] = {
    {"rcInitialize", rcInitialize, METH_VARARGS,
        "Initialize RoboticsCape hard- and software."},
    {"rcCleanup", rcCleanup, METH_VARARGS,
        "Shut down RoboticsCape library and functions."},
    {"rcGetState", rcGetState, METH_VARARGS,
        "Get high level robot state."},
    {"rcPrintState", rcPrintState, METH_VARARGS,
        "Print textual representation of high level robot state."},
    {"rcGetEncoderPos", rcGetEncoderPos, METH_VARARGS,
        "Get quadrature encoder position for given channel or for all channels."},
    {"rcBatteryVoltage", rcBatteryVoltage, METH_VARARGS,
        "Get LiPo battery voltage."},
    {"rcDCJackVoltage", rcDCJackVoltage, METH_VARARGS,
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
