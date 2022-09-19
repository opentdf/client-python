#!/bin/bash
set -ex

# Install opentdf cpp library
rm -rf build
mkdir build
cd build
conan install .. --build=missing

# Build whl
cd ../src/module
python3.8 setup.py bdist_wheel 
python3.9 setup.py bdist_wheel 
python3.10 setup.py bdist_wheel