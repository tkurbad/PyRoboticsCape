#!/usr/bin/env python3

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

setup(
    name = 'roboticscape',
	version = '0.1',
	description = 'Python bindings for libroboticscape',
	author = 'Torsten Kurbad',
	author_email = 'beaglebone@tk-webart.de',
	maintainer = 'Torsten Kurbad',
	maintainer_email = 'beaglebone@tk-webart.de',
	license = 'MIT',
	url = 'https://github.com/StrawsonDesign/Robotics_Cape_Installer',
	ext_modules = [
        Extension('roboticscape',
                  ['roboticscapemodule.c'],
                  extra_compile_args = ['-I.'],
                  extra_link_args = ['-lroboticscape'])],
)
