#
# __init__.py - Python bindings for Strawson Design's libroboticscape
# Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
#

from _roboticscape import *

# Return values of rcGetState(), input to rcSetState()
STATE = dict(
    UNINITIALIZED   = 0,
    RUNNING         = 1,
    PAUSED          = 2,
    EXITING         = 3,
)

def rcGetStateAsName():
    state = rcGetState()
    return list(STATE.keys())[list(STATE.values()).index(state)]
