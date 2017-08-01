#!/usr/bin/env python3

try:
    from setuptools import find_packages, setup, Extension
except ImportError:
    from distutils.core import find_packages, setup, Extension

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
    package_dir={"": "src"},
    packages=find_packages(where="src"),
	ext_modules = [
        Extension('roboticscape',
                  ['src/roboticscapemodule.c'],
                  extra_compile_args = ['-Isrc'],
                  extra_link_args = ['-lroboticscape'])],
)
