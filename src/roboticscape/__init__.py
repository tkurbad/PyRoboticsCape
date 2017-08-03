#
# __init__.py - Python bindings for Strawson Design's libroboticscape
# Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
#

import atexit

from _roboticscape import *
from enum import IntEnum

# Type definitions
class State(IntEnum):
    """ Enumeration of possible states from rcGetState(), and for
        rcSetState()
    """
    UNINITIALIZED   = 0
    RUNNING         = 1
    PAUSED          = 2
    EXITING         = 3

class PowerState(IntEnum):
    """ Enumeration of possible power states. """
    OFF             = 0
    ON              = 1

class LED(IntEnum):
    """ Enumeration of available LEDs. """
    GREEN           = 0
    RED             = 1

class Button(IntEnum):
    """ Enumeration of available buttons. """
    PAUSE           = 0
    MODE            = 1

class ButtonState(IntEnum):
    """ Enumeration of possible button states. """
    RELEASED        = 0
    PRESSED         = 1


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


# Event handlers
""" Call the cleanup method on exit. """
atexit.register(rcCleanup)
