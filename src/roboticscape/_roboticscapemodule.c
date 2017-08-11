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

    // Work around rc_get_led, since it fails reading from /sys/gpio
    if (led == 0) {
        state = rc_gpio_get_value_mmap(GRN_LED);
    } else {
		state = rc_gpio_get_value_mmap(RED_LED);
    }

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

static PyObject *rcGetButton(PyObject *self, PyObject *args) {
    int state;
    int button;

    if (!PyArg_ParseTuple(args, "i", &button)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (pause or mode button) required.");
        return NULL;
    }

    if ((button < 0) || (button > 1)) {
        PyErr_SetString(PyExc_ValueError, "Button argument has to be pause (0) or mode (1).");
        return NULL;
    }

    if (button == 0)
        state = rc_get_pause_button();
    else
        state = rc_get_mode_button();

    return Py_BuildValue("i", state);
}

static PyObject *rcEnableMotors(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_enable_motors();

    return Py_BuildValue("i", retval);
}

static PyObject *rcDisableMotors(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_disable_motors();

    return Py_BuildValue("i", retval);
}

static PyObject *rcSetMotor(PyObject *self, PyObject *args) {
    int retval;
    int motor;
    float duty;

    if (!PyArg_ParseTuple(args, "if", &motor, &duty)) {
        PyErr_SetString(PyExc_ValueError, "Integer and float argument (motor number, duty cycle) required.");
        return NULL;
    }

    if ((motor < 1) || (motor > 8)) {
        PyErr_SetString(PyExc_ValueError, "Motor number has to be >= 1 and <= 4.");
        return NULL;
    }

    if ((duty < -1.0) || (duty > 1.0)) {
        PyErr_SetString(PyExc_ValueError, "Duty cycle has to be >= -1.0 and <= 1.0.");
        return NULL;
    }

    retval = rc_set_motor(motor, duty);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSetMotorAll(PyObject *self, PyObject *args) {
    int retval;
    float duty;

    if (!PyArg_ParseTuple(args, "f", &duty)) {
        PyErr_SetString(PyExc_ValueError, "Float argument (duty cycle) required.");
        return NULL;
    }

    if ((duty < -1.0) || (duty > 1.0)) {
        PyErr_SetString(PyExc_ValueError, "Duty cycle has to be >= -1.0 and <= 1.0.");
        return NULL;
    }

    retval = rc_set_motor_all(duty);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSetMotorFreeSpin(PyObject *self, PyObject *args) {
    int retval;
    int motor;

    if (!PyArg_ParseTuple(args, "i", &motor)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (motor number) required.");
        return NULL;
    }

    if ((motor < 1) || (motor > 8)) {
        PyErr_SetString(PyExc_ValueError, "Motor number has to be >= 1 and <= 4.");
        return NULL;
    }

    retval = rc_set_motor_free_spin(motor);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSetMotorFreeSpinAll(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_set_motor_free_spin_all();

    return Py_BuildValue("i", retval);
}

static PyObject *rcSetMotorBrake(PyObject *self, PyObject *args) {
    int retval;
    int motor;

    if (!PyArg_ParseTuple(args, "i", &motor)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (motor number) required.");
        return NULL;
    }

    if ((motor < 1) || (motor > 8)) {
        PyErr_SetString(PyExc_ValueError, "Motor number has to be >= 1 and <= 4.");
        return NULL;
    }

    retval = rc_set_motor_brake(motor);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSetMotorBrakeAll(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_set_motor_brake_all();

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

    retval = rc_set_encoder_pos(channel, position);

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

static PyObject *rcSendServoPulseUs(PyObject *self, PyObject *args) {
    int retval;
    int channel;
    int us;

    if (!PyArg_ParseTuple(args, "ii", &channel, &us)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (servo channel, microseconds) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 8)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 8.");
        return NULL;
    }

    retval = rc_send_servo_pulse_us(channel, us);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendServoPulseUsAll(PyObject *self, PyObject *args) {
    int retval;
    int us;

    if (!PyArg_ParseTuple(args, "i", &us)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (microseconds) required.");
        return NULL;
    }

    retval = rc_send_servo_pulse_us_all(us);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendServoPulseNormalized(PyObject *self, PyObject *args) {
    int retval;
    int channel;
    float input;

    if (!PyArg_ParseTuple(args, "if", &channel, &input)) {
        PyErr_SetString(PyExc_ValueError, "Integer and float arguments (servo channel, normalized input) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 8)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 8.");
        return NULL;
    }

    if ((input < -1.5) || (input > 1.5)) {
        PyErr_SetString(PyExc_ValueError, "Normalized input has to be >= -1.5 and <= 1.5.");
        return NULL;
    }

    retval = rc_send_servo_pulse_normalized(channel, input);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendServoPulseNormalizedAll(PyObject *self, PyObject *args) {
    int retval;
    float input;

    if (!PyArg_ParseTuple(args, "f", &input)) {
        PyErr_SetString(PyExc_ValueError, "Float argument (normalized input) required.");
        return NULL;
    }

    if ((input < -1.5) || (input > 1.5)) {
        PyErr_SetString(PyExc_ValueError, "Normalized input has to be >= -1.5 and <= 1.5.");
        return NULL;
    }

    retval = rc_send_servo_pulse_normalized_all(input);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendESCPulseNormalized(PyObject *self, PyObject *args) {
    int retval;
    int channel;
    float input;

    if (!PyArg_ParseTuple(args, "if", &channel, &input)) {
        PyErr_SetString(PyExc_ValueError, "Integer and float argument (ESC channel, normalized input) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 8)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 8.");
        return NULL;
    }

    if ((input < -0.1) || (input > 1.0)) {
        PyErr_SetString(PyExc_ValueError, "Normalized input has to be >= -0.1 and <= 1.0.");
        return NULL;
    }

    retval = rc_send_esc_pulse_normalized(channel, input);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendESCPulseNormalizedAll(PyObject *self, PyObject *args) {
    int retval;
    float input;

    if (!PyArg_ParseTuple(args, "f", &input)) {
        PyErr_SetString(PyExc_ValueError, "Float argument (normalized input) required.");
        return NULL;
    }

    if ((input < -0.1) || (input > 1.0)) {
        PyErr_SetString(PyExc_ValueError, "Normalized input has to be >= -0.1 and <= 1.0.");
        return NULL;
    }

    retval = rc_send_esc_pulse_normalized_all(input);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendOneshotPulseNormalized(PyObject *self, PyObject *args) {
    int retval;
    int channel;
    float input;

    if (!PyArg_ParseTuple(args, "if", &channel, &input)) {
        PyErr_SetString(PyExc_ValueError, "Integer and float argument (channel, normalized input) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 8)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 8.");
        return NULL;
    }

    if ((input < -0.1) || (input > 1.0)) {
        PyErr_SetString(PyExc_ValueError, "Normalized input has to be >= -0.1 and <= 1.0.");
        return NULL;
    }

    retval = rc_send_oneshot_pulse_normalized(channel, input);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendOneshotPulseNormalizedAll(PyObject *self, PyObject *args) {
    int retval;
    float input;

    if (!PyArg_ParseTuple(args, "f", &input)) {
        PyErr_SetString(PyExc_ValueError, "Float argument (normalized input) required.");
        return NULL;
    }

    if ((input < -0.1) || (input > 1.0)) {
        PyErr_SetString(PyExc_ValueError, "Normalized input has to be >= -0.1 and <= 1.0.");
        return NULL;
    }

    retval = rc_send_oneshot_pulse_normalized_all(input);

    return Py_BuildValue("i", retval);
}

static PyObject *rcInitializeDSM(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_initialize_dsm();

    return Py_BuildValue("i", retval);
}

static PyObject *rcStopDSMService(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_stop_dsm_service();

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetDSMChRaw(PyObject *self, PyObject *args) {
    int rawvalue;
    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (DSM channel number) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 9)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 9.");
        return NULL;
    }

    rawvalue = rc_get_dsm_ch_raw(channel);

    return Py_BuildValue("i", rawvalue);
}

static PyObject *rcGetDSMChNormalized(PyObject *self, PyObject *args) {
    float normalized;
    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (DSM channel number) required.");
        return NULL;
    }

    if ((channel < 1) || (channel > 9)) {
        PyErr_SetString(PyExc_ValueError, "Channel number has to be >= 1 and <= 9.");
        return NULL;
    }

    normalized = rc_get_dsm_ch_normalized(channel);

    return Py_BuildValue("f", normalized);
}

static PyObject *rcIsDSMNewData(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_is_new_dsm_data();

    return Py_BuildValue("i", retval);
}

static PyObject *rcIsDSMActive(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_is_dsm_active();

    return Py_BuildValue("i", retval);
}

static PyObject *rcNanosSinceLastDSMPacket(PyObject *self, PyObject *args) {
    long nanos;

    nanos = rc_nanos_since_last_dsm_packet();

    return PyLong_FromUnsignedLongLong(nanos);
}

static PyObject *rcGetDSMResolution(PyObject *self, PyObject *args) {
    int resolution;

    resolution = rc_get_dsm_resolution();

    return Py_BuildValue("i", resolution);
}

static PyObject *rcNumDSMChannels(PyObject *self, PyObject *args) {
    int num_channels;

    num_channels = rc_num_dsm_channels();

    return Py_BuildValue("i", num_channels);
}

static PyObject *rcBindDSM(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_bind_dsm();

    return Py_BuildValue("i", retval);
}

static PyObject *rcCalibrateDSMRoutine(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_calibrate_dsm_routine();

    return Py_BuildValue("i", retval);
}

// TODO: IMU methods

static PyObject *_rcInitializeBarometer(PyObject *self, PyObject *args) {
    int retval;
    int oversample;
    int filter;

    if (!PyArg_ParseTuple(args, "ii", &oversample, &filter)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (oversample setting, filter setting) required.");
        return NULL;
    }

    if ((oversample < 4) || (oversample > 20) || (oversample % 4 != 0)) {
        PyErr_SetString(PyExc_ValueError, "Allowed oversample values: 4, 8, 12, 16, or 20.");
        return NULL;
    }

    if ((filter < 0) || (filter > 16) || (filter % 4 != 0)) {
        PyErr_SetString(PyExc_ValueError, "Allowed filter values: 0, 4, 8, 12, or 16.");
        return NULL;
    }

    retval = rc_initialize_barometer(oversample, filter);

    return Py_BuildValue("i", retval);
}

static PyObject *rcPowerOffBarometer(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_power_off_barometer();

    return Py_BuildValue("i", retval);
}

static PyObject *rcReadBarometer(PyObject *self, PyObject *args) {
    int retval;

    retval = rc_read_barometer();

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetBMPTemperature(PyObject *self, PyObject *args) {
    float celsius;

    celsius = rc_bmp_get_temperature();

    return Py_BuildValue("f", celsius);
}

static PyObject *rcGetBMPPressurePa(PyObject *self, PyObject *args) {
    float pa;

    pa = rc_bmp_get_pressure_pa();

    return Py_BuildValue("f", pa);
}

static PyObject *rcGetBMPAltitudeM(PyObject *self, PyObject *args) {
    float meters;

    meters = rc_bmp_get_altitude_m();

    return Py_BuildValue("f", meters);
}

static PyObject *rcSetBMPSeaLevelPressurePa(PyObject *self, PyObject *args) {
    int retval;
    float pa;

    if (!PyArg_ParseTuple(args, "f", &pa)) {
        PyErr_SetString(PyExc_ValueError, "Float argument (pressure in pascal) required.");
        return NULL;
    }

    if ((pa < 80000.0) || (pa > 120000.0)) {
        PyErr_SetString(PyExc_ValueError, "Pressure in pascal must be >= 80,000 and <= 120,000.");
        return NULL;
    }

    retval = rc_set_sea_level_pressure_pa(pa);

    return Py_BuildValue("i", retval);
}

static PyObject *rcInitializeI2C(PyObject *self, PyObject *args) {
    int retval;
    int bus;
    int address;

    if (!PyArg_ParseTuple(args, "ii", &bus, &address)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (bus number, device address) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    if ((address < 0x03) || (address > 0x77)) {
        PyErr_SetString(PyExc_ValueError, "Device address must be >= 0x03 and <= 0x77.");
        return NULL;
    }

    retval = rc_i2c_init(bus, (uint8_t)address);

    return Py_BuildValue("i", retval);
}

static PyObject *rcCloseI2C(PyObject *self, PyObject *args) {
    int retval;
    int bus;

    if (!PyArg_ParseTuple(args, "i", &bus)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (bus number) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    retval = rc_i2c_close(bus);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSetI2CDeviceAddress(PyObject *self, PyObject *args) {
    int retval;
    int bus;
    int address;

    if (!PyArg_ParseTuple(args, "ii", &bus, &address)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (bus number, device address) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    if ((address < 0x03) || (address > 0x77)) {
        PyErr_SetString(PyExc_ValueError, "Device address must be >= 0x03 and <= 0x77.");
        return NULL;
    }

    retval = rc_i2c_set_device_address(bus, (uint8_t)address);

    return Py_BuildValue("i", retval);
}

static PyObject *rcClaimI2CBus(PyObject *self, PyObject *args) {
    int retval;
    int bus;

    if (!PyArg_ParseTuple(args, "i", &bus)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (bus number) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    retval = rc_i2c_claim_bus(bus);

    return Py_BuildValue("i", retval);
}

static PyObject *rcReleaseI2CBus(PyObject *self, PyObject *args) {
    int retval;
    int bus;

    if (!PyArg_ParseTuple(args, "i", &bus)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (bus number) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    retval = rc_i2c_release_bus(bus);

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetI2CBusInUse(PyObject *self, PyObject *args) {
    int state;
    int bus;

    if (!PyArg_ParseTuple(args, "i", &bus)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (bus number) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    state = rc_i2c_get_in_use_state(bus);

    return Py_BuildValue("i", state);
}

static PyObject *rcReadI2CByte(PyObject *self, PyObject *args) {
    int retval;
    int bus;
    int address;
    uint8_t data;

    if (!PyArg_ParseTuple(args, "ii", &bus, &address)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (bus number, register address) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    if ((address < 0x00) || (address > 0xff)) {
        PyErr_SetString(PyExc_ValueError, "Register address must be >= 0x00 and <= 0xff.");
        return NULL;
    }

    retval = rc_i2c_read_byte(bus, (uint8_t)address, &data);

    if (retval != 0) {
        PyErr_SetString(PyExc_ValueError, "Reading one byte from I²C device failed.");
        return NULL;
    }

    return Py_BuildValue("i", data);
}

static PyObject *rcReadI2CBytes(PyObject *self, PyObject *args) {
// int (int bus, uint8_t regAddr, uint8_t length,  uint8_t *data);
    int retval;
    int bus;
    int address;
    int length;
    uint8_t *data;

    if (!PyArg_ParseTuple(args, "ii", &bus, &address)) {
        PyErr_SetString(PyExc_ValueError, "Three integer arguments (bus number, register address, data length) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    if ((address < 0x00) || (address > 0xff)) {
        PyErr_SetString(PyExc_ValueError, "Register address must be >= 0x00 and <= 0xff.");
        return NULL;
    }

    if ((length < 1) || (length > 128)) {
        PyErr_SetString(PyExc_ValueError, "Data length must be > 0 and <= 128.");
        return NULL;
    }

    retval = rc_i2c_read_bytes(bus, (uint8_t)address, (uint8_t)length, &data);

    if (retval != 0) {
        PyErr_SetString(PyExc_ValueError, "Reading one byte from I²C device failed.");
        return NULL;
    }

    return Py_BuildValue("y*", data);
}

static PyObject *rcReadI2CWord(PyObject *self, PyObject *args) {
    int retval;
    int bus;
    int address;
    uint16_t data;

    if (!PyArg_ParseTuple(args, "ii", &bus, &address)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (bus number, register address) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    if ((address < 0x00) || (address > 0xff)) {
        PyErr_SetString(PyExc_ValueError, "Register address must be >= 0x00 and <= 0xff.");
        return NULL;
    }

    retval = rc_i2c_read_word(bus, (uint8_t)address, &data);

    if (retval != 0) {
        PyErr_SetString(PyExc_ValueError, "Reading one word from I²C device failed.");
        return NULL;
    }

    return Py_BuildValue("i", data);
}

static PyObject *rcReadI2CWords(PyObject *self, PyObject *args) {
//int rc_i2c_read_words(int bus, uint8_t regAddr, uint8_t length, uint16_t *data);
    
}

static PyObject *rcReadI2CBit(PyObject *self, PyObject *args) {
    int retval;
    int bus;
    int address;
    int bitnum;
    uint8_t data;

    if (!PyArg_ParseTuple(args, "iii", &bus, &address, &bitnum)) {
        PyErr_SetString(PyExc_ValueError, "Three integer arguments (bus number, register address, bit number) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    if ((address < 0x00) || (address > 0xff)) {
        PyErr_SetString(PyExc_ValueError, "Register address must be >= 0x00 and <= 0xff.");
        return NULL;
    }

    if ((bitnum < 0) || (bitnum > 15)) {
        PyErr_SetString(PyExc_ValueError, "Bit number must be >= 0 and <= 15.");
        return NULL;
    }

    retval = rc_i2c_read_bit(bus, (uint8_t)address, (uint8_t)bitnum, &data);

    if (retval != 0) {
        PyErr_SetString(PyExc_ValueError, "Reading one bit from I²C device failed.");
        return NULL;
    }

    return Py_BuildValue("i", data);
}

static PyObject *rcWriteI2CByte(PyObject *self, PyObject *args) {
//int rc_i2c_write_byte(int bus, uint8_t regAddr, uint8_t data);
    
}

static PyObject *rcWriteI2CBytes(PyObject *self, PyObject *args) {
//int rc_i2c_write_bytes(int bus, uint8_t regAddr, uint8_t length, uint8_t* data);
    
}

static PyObject *rcWriteI2CWord(PyObject *self, PyObject *args) {
//int rc_i2c_write_word(int bus, uint8_t regAddr, uint16_t data);
    
}

static PyObject *rcWriteI2CWords(PyObject *self, PyObject *args) {
//int rc_i2c_write_words(int bus, uint8_t regAddr, uint8_t length, uint16_t* data);
    
}

static PyObject *rcWriteI2CBit(PyObject *self, PyObject *args) {
//int rc_i2c_write_bit(int bus, uint8_t regAddr, uint8_t bitNum, uint8_t data);
    
}

static PyObject *rcSendI2CByte(PyObject *self, PyObject *args) {
    int retval;
    int bus;
    uint8_t data;

    if (!PyArg_ParseTuple(args, "iB", &bus, &data)) {
        PyErr_SetString(PyExc_ValueError, "Two integer arguments (bus number, data byte) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    retval = rc_i2c_send_byte(bus, data);

    return Py_BuildValue("i", retval);
}

static PyObject *rcSendI2CBytes(PyObject *self, PyObject *args) {
    int retval;
    int bus;
    uint8_t length;
    uint8_t *data;

    if (!PyArg_ParseTuple(args, "iBy*", &bus, &length, &data)) {
        PyErr_SetString(PyExc_ValueError, "Three integer arguments (bus number, data length, data bytes) required.");
        return NULL;
    }

    if ((bus < 1) || (bus > 2)) {
        PyErr_SetString(PyExc_ValueError, "Bus number must be 1 or 2.");
        return NULL;
    }

    retval = rc_i2c_send_bytes(bus, length, data);

    return Py_BuildValue("i", retval);
}


static PyObject *rcSetCPUFreq(PyObject *self, PyObject *args) {
    int retval;
    int frequency;

    if (!PyArg_ParseTuple(args, "i", &frequency)) {
        PyErr_SetString(PyExc_ValueError, "Integer argument (frequency enumeration) required.");
        return NULL;
    }

    if ((frequency < 0) || (frequency > 4)) {
        PyErr_SetString(PyExc_ValueError, "Frequency enumeration value must be >= 0 and <= 4.");
        return NULL;
    }

    retval = rc_set_cpu_freq(frequency);

    return Py_BuildValue("i", retval);
}

static PyObject *rcGetCPUFreq(PyObject *self, PyObject *args) {
    rc_cpu_freq_t frequency;

    frequency = rc_get_cpu_freq();

    return Py_BuildValue("i", frequency);
}

static PyObject *rcGetBBModel(PyObject *self, PyObject *args) {
    rc_bb_model_t model;

    model = rc_get_bb_model();

    return Py_BuildValue("i", model);
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
