#
# __init__.py - Python bindings for Strawson Design's libroboticscape
# Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
#

from _roboticscape import *
from enum import IntEnum

# Return values of rcGetState(), input to rcSetState()
class State(IntEnum):
    UNINITIALIZED   = 0
    RUNNING         = 1
    PAUSED          = 2
    EXITING         = 3

def rcGetStateAsName():
    state = rcGetState()
    return State(state).name
