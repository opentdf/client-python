#!/bin/bash
set -ex
export OPENTDF_BUILD="build"
export WHEEL_OSX_PLAT_NAME="macosx_10_14_x86_64"


rm -rf $OPENTDF_BUILD
mkdir $OPENTDF_BUILD

cd $OPENTDF_BUILD
conan install .. --build=missing
conan build .. -bf .

cd ../src/python-bindings/pips
python3.10 -m pip install --upgrade pip
python3.10 -m pip install pybind11 twine
python3.10 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME