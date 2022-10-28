#!/bin/bash
set -x
export OPENTDF_BUILD="build"
export OPENTDF_DST="opentdf-cpp"
export WHEEL_OSX_PLAT_NAME="macosx_10_14_x86_64"

rm -rf $OPENTDF_DST
rm -rf $OPENTDF_BUILD
mkdir $OPENTDF_BUILD
mkdir $OPENTDF_DST
mkdir $OPENTDF_DST/lib
mkdir $OPENTDF_DST/include

cd $OPENTDF_BUILD
conan --version
conan install .. --build=missing

cd ../src/python-bindings/pips
if [[ $OSTYPE == "darwin"* ]]; then
  python -m pip install --upgrade pip
  python -m pip install wheel pybind11 twine
  python setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME
fi