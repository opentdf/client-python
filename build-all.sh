#!/bin/bash
set -ex

# Install opentdf cpp library
mkdir opentdf-cpp
ls -al
rm -rf build
mkdir build
ls -al
cd build
conan install .. --build=missing
ls -al ../opentdf-cpp
# Build whl
cd ../src/module
ls -al
# FIXME: Find python versions and build the whl's
# python3.8 -m pip install --upgrade pip
# python3.8 -m pip install pybind11 twine
# python3.8 setup.py bdist_wheel 

# python3.9 -m pip install --upgrade pip
# python3.9 -m pip install pybind11 twine
# python3.9 setup.py bdist_wheel 

# python3.10 -m pip install --upgrade pip
# python3.10 -m pip install pybind11 twine
# python3.10 setup.py bdist_wheel


python3 -m pip install --upgrade pip
python3 -m pip install pybind11 twine
python3 setup.py bdist_wheel 