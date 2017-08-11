#
# __init__.py - Python bindings for Strawson Design's libroboticscape
# Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
#

import atexit
from enum import IntEnum

import _roboticscape
from _roboticscape import *

# Meta definitions
class MyIntEnum(IntEnum):
    """ Add class method has_value to IntEnum to check whether a certain
        value exists in an enum.
    """
    @classmethod
    def has_value(cls, value):
        return (any(value == item.value for item in cls))


# Type definitions
class State(MyIntEnum):
    """ Enumeration of possible states from rcGetState(), and for
        rcSetState()
    """
    UNINITIALIZED   = 0
    RUNNING         = 1
    PAUSED          = 2
    EXITING         = 3


class PowerState(MyIntEnum):
    """ Enumeration of possible power states. """
    OFF             = 0
    ON              = 1


class LED(MyIntEnum):
    """ Enumeration of available LEDs. """
    GREEN           = 0
    RED             = 1


class Button(MyIntEnum):
    """ Enumeration of available buttons. """
    PAUSE           = 0
    MODE            = 1


class ButtonState(MyIntEnum):
    """ Enumeration of possible button states. """
    RELEASED        = 0
    PRESSED         = 1


class BMPOversample(MyIntEnum):
    """ Enumeration of BMP280 oversample settings. """
    BMP_OVERSAMPLE_1    = 4     # update rate 182 HZ
    BMP_OVERSAMPLE_2    = 8     # update rate 133 HZ
    BMP_OVERSAMPLE_4    = 12    # update rate 87 HZ
    BMP_OVERSAMPLE_8    = 16    # update rate 51 HZ
    BMP_OVERSAMPLE_16   = 20    # update rate 28 HZ


class BMPFilter(MyIntEnum):
    """ Enumeration of BMP280 filter settings. """
    BMP_FILTER_OFF      = 0
    BMP_FILTER_2        = 4
    BMP_FILTER_4        = 8
    BMP_FILTER_8        = 12
    BMP_FILTER_16       = 16


# High level methods
def rcGetStateAsEnum():
    """ Get the current robot state as Python Enum. """
    state = rcGetState()
    return State(state)

def rcGetGreenLED():
    """ Get state of green LED as Enum. """
    return PowerState(rcGetLED(LED.GREEN.value))

def rcGetRedLED():
    """ Get state of red LED as Enum. """
    return PowerState(rcGetLED(LED.RED.value))

def rcSetGreenLEDOn():
    """ Turn green LED on. """
    return rcSetLED(LED.GREEN.value, PowerState.ON.value)

def rcSetGreenLEDOff():
    """ Turn green LED off. """
    return rcSetLED(LED.GREEN.value, PowerState.OFF.value)

def rcSetRedLEDOn():
    """ Turn red LED on. """
    return rcSetLED(LED.RED.value, PowerState.ON.value)

def rcSetRedLEDOff():
    """ Turn red LED off. """
    return rcSetLED(LED.RED.value, PowerState.OFF.value)

def rcGetModeButton():
    """ Get state of mode button as Enum. """
    return ButtonState(rcGetButton(Button.MODE.value))

def rcGetPauseButton():
    """ Get state of pause button as Enum. """
    return ButtonState(rcGetButton(Button.PAUSE.value))

def rcInitializeBarometer(
    bmpOversample = BMPOversample.BMP_OVERSAMPLE_1.value,
    bmpFilter = BMPFilter.BMP_FILTER_OFF.value):
    """ Initialize and power on barometer. """
    if not BMPOversample.has_value(bmpOversample):
        raise(ValueError('oversample value %d not allowed' % bmpOversample))
    if not BMPFilter.has_value(bmpFilter):
        raise(ValueError('filter value %d not allowed' % bmpFilter))
    return _roboticscape._rcInitializeBarometer(bmpOversample, bmpFilter)


# Event handlers
""" Call the cleanup method on exit. """
atexit.register(rcCleanup)
