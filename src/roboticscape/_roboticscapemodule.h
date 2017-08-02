/*
 * roboticscapemodule.h - Python bindings for Strawson Design's
 * libroboticscape
 * 
 * Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
 *
 */

#include <Python.h>
#include <roboticscape.h>


// Method headers
static PyObject *rcInitialize(PyObject *self, PyObject *args);
static PyObject *rcCleanup(PyObject *self, PyObject *args);

static PyObject *rcGetState(PyObject *self, PyObject *args);
static PyObject *rcSetState(PyObject *self, PyObject *args);

static PyObject *rcGetLED(PyObject *self, PyObject *args);
static PyObject *rcSetLED(PyObject *self, PyObject *args);
static PyObject *rcBlinkLED(PyObject *self, PyObject *args);

static PyObject *rcGetEncoderPos(PyObject *self, PyObject *args);
static PyObject *rcSetEncoderPos(PyObject *self, PyObject *args);

static PyObject *rcBatteryVoltage(PyObject *self, PyObject *args);
static PyObject *rcDCJackVoltage(PyObject *self, PyObject *args);

static PyObject *rcADCRaw(PyObject *self, PyObject *args);
static PyObject *rcADCVolt(PyObject *self, PyObject *args);

static PyObject *rcEnableServoPowerRail(PyObject *self, PyObject *args);
static PyObject *rcDisableServoPowerRail(PyObject *self, PyObject *args);

// TODO: Implement rcGetPauseButton() and rcGetModeButton in Python
static PyObject *rcGetButton(PyObject *self, PyObject *args);


// Method definitions
static PyMethodDef RoboticsCapeMethods[] = {
    {"rcInitialize", rcInitialize, METH_NOARGS,
        "Initialize RoboticsCape hard- and software."},
    {"rcCleanup", rcCleanup, METH_NOARGS,
        "Shut down RoboticsCape library and functions."},
    {"rcGetState", rcGetState, METH_NOARGS,
        "Get high level robot state."},
    {"rcSetState", rcSetState, METH_VARARGS,
        "Set high level robot state."},
    {"rcGetLED", rcGetLED, METH_VARARGS,
        "Get state of green or red LED (0 = off, 1 = on)."},
    {"rcSetLED", rcSetLED, METH_VARARGS,
        "Turn on/off green or red LED (0 = off, 1 = on)."},
    {"rcBlinkLED", rcBlinkLED, METH_VARARGS,
        "Blink green or red LED with a given frequency (Hz) for a finite period (s)."},
    {"rcGetEncoderPos", rcGetEncoderPos, METH_VARARGS,
        "Get quadrature encoder position for given channel (1-4)."},
    {"rcSetEncoderPos", rcSetEncoderPos, METH_VARARGS,
        "Set quadrature encoder position for given channel (1-4)."},
    {"rcBatteryVoltage", rcBatteryVoltage, METH_NOARGS,
        "Get LiPo battery voltage."},
    {"rcDCJackVoltage", rcDCJackVoltage, METH_NOARGS,
        "Get DC jack voltage."},
    {"rcADCRaw", rcADCRaw, METH_VARARGS,
        "Get raw ADC value for given channel (0-6)."},
    {"rcADCVolt", rcADCVolt, METH_VARARGS,
        "Get ADC voltage for given channel (0-6)."},
    {"rcEnableServoPowerRail", rcEnableServoPowerRail, METH_NOARGS,
        "Enable Servo 6V Power Rail."},
    {"rcDisableServoPowerRail", rcDisableServoPowerRail, METH_NOARGS,
        "Enable Servo 6V Power Rail."},
    {"rcGetButton", rcGetButton, METH_VARARGS,
        "Get state of pause (0) or mode (1) button (0 = released, 1 = pressed)."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};


// Module defintion
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
