#
# __init__.py - Python bindings for Strawson Design's libroboticscape
# Copyright (C) 2017 Torsten Kurbad <beaglebone@tk-webart.de>
#

# Bootstrap
def __bootstrap__():
    global __bootstrap__, __loader__, __file__
    import sys, pkg_resources, imp
    __file__ = pkg_resources.resource_filename(__name__, 'roboticscape.cpython-34m.so')
    __loader__ = None; del __bootstrap__, __loader__
    imp.load_dynamic(__name__, __file__)

__bootstrap__()
