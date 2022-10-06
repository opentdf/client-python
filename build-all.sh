#!/bin/bash
set -ex
export OPENTDF_BUILD="build"
export OPENTDF_DST="opentdf-cpp"
export WHEEL_OSX_PLAT_NAME="macosx_10_14_x86_64"


rm -rf $OPENTDF_BUILD
mkdir $OPENTDF_BUILD
mkdir -p $OPENTDF_DST
mkdir $OPENTDF_DST/lib
mkdir $OPENTDF_DST/include
ls
cd $OPENTDF_BUILD
conan --version
conan install .. --build=missing

ls ../opentdf-cpp/lib
ls ../opentdf-cpp/include
pwd
cd ../src/python-bindings/pips
if [[ $OSTYPE == "darwin"* ]]; then
  python -m pip install --upgrade pip
  python -m pip install wheel pybind11 twine
  python setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME
fi