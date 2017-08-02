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
        return NULL;
    }

    if ((state < 0) || (state > 3)) {
        PyErr_SetString(PyExc_ValueError, "State has to be >= 0 and <= 3.");
        return NULL;
    }

    retval = rc_set_state(state);

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetLED(PyObject *self, PyObject *args) {
    int state;
    int led;

    if (!PyArg_ParseTuple(args, "i", &led)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (green or red LED) required.");
        return NULL;
    }

    if ((led < 0) || (led > 1)) {
        PyErr_SetString(PyExc_ValueError, "LED argument has to be green (0) or red (1).");
        return NULL;
    }

    state = rc_get_led(led);

    return Py_BuildValue("i", state);
}

static PyObject *rcSetLED(PyObject *self, PyObject *args) {
    int retval;
    int led;
    int state;

    if (!PyArg_ParseTuple(args, "ii", &led, &state)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (green or red LED, on or off) required.");
        return NULL;
    }

    if ((led < 0) || (led > 1)) {
        PyErr_SetString(PyExc_ValueError, "LED argument has to be green (0) or red (1).");
        return NULL;
    }

    if ((state < 0) || (state > 1)) {
        PyErr_SetString(PyExc_ValueError, "State argument has to be off (0) or on (1).");
        return NULL;
    }
    retval = rc_set_led(led, state);

    return Py_BuildValue("i", retval);
}

static PyObject *rcBlinkLED(PyObject *self, PyObject *args) {
    int retval;
    int led;
    float hz;
    float period;

    if (!PyArg_ParseTuple(args, "iff", &led, &hz, &period)) {
        PyErr_SetString(PyExc_ValueError, "One integer and two float arguments (green or red LED, frequency, time period) required.");
        return NULL;
    }

    if ((led < 0) || (led > 1)) {
        PyErr_SetString(PyExc_ValueError, "LED argument has to be green (0) or red (1).");
        return NULL;
    }

    if (hz <= 0.0) {
        PyErr_SetString(PyExc_ValueError, "Frequency must be > 0.");
        return NULL;
    }

    if (period <= 0.0) {
        PyErr_SetString(PyExc_ValueError, "Time period must be > 0.");
        return NULL;
    }

    retval = rc_blink_led(led, hz, period);

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetEncoderPos(PyObject *self, PyObject *args) {
    long position;
    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (encoder channel number) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 4)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 4.");
        return NULL;
    }

    position = (long)rc_get_encoder_pos(channel);

    return Py_BuildValue("l", position);
}

static PyObject *rcSetEncoderPos(PyObject *self, PyObject *args) {
    int retval;
    int position;
    int channel;

    if (!PyArg_ParseTuple(args, "ii", &channel, &position)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (encoder channel number, position) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 4)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 4.");
        return NULL;
    }

    retval = rc_get_encoder_pos(channel, position);

    return Py_BuildValue("l", retval);
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

static PyObject *rcADCRaw(PyObject *self, PyObject *args) {
    int rawvalue;
    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (ADC channel number) required.");
        return NULL;
    }

    if ((channel < 0) || (channel > 6)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 0 and <= 6.");
        return NULL;
    }

    rawvalue = rc_adc_raw(channel);

    return Py_BuildValue("i", rawvalue);
}

static PyObject *rcADCVolt(PyObject *self, PyObject *args) {
    float voltage;
    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (ADC channel number) required.");
        return NULL;
    }

    if ((channel < 0) || (channel > 6)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 0 and <= 6.");
        return NULL;
    }

    voltage = rc_adc_volt(channel);

    return Py_BuildValue("f", voltage);
}

static PyObject *rcEnableServoPowerRail(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_enable_servo_power_rail();

    return Py_BuildValue("i", retval);
}

static PyObject *rcDisableServoPowerRail(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_disable_servo_power_rail();

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetButton(PyObject *self, PyObject *args) {
    int state;
    int button;

    if (!PyArg_ParseTuple(args, "i", &button)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (pause or mode button) required.");
        return NULL;
    }

    if ((button < 0) || (led > button)) {
        PyErr_SetString(PyExc_ValueError, "Button argument has to be pause (0) or mode (1).");
        return NULL;
    }

    if (button == 0)
        state = rc_get_pause_button();
    else
        state = rc_get_mode_button();

    return Py_BuildValue("i", state);
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
