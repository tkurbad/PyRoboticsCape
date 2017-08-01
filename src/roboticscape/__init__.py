#
# __init__.py - Python bindings for Strawson Design's libroboticscape
# Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
#

from _roboticscape import *
from enum import IntEnum

class State(IntEnum):
    """ Enumeration of possible states from rcGetState(), and for
        rcSetState()
    """
    UNINITIALIZED   = 0
    RUNNING         = 1
    PAUSED          = 2
    EXITING         = 3


def rcGetStateAsName():
    """ Get the current robot state as human readable value """
    state = rcGetState()
    return State(state).name
