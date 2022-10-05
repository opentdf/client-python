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
conan install .. --build=missing

ls ../opentdf-cpp/lib
ls ../opentdf-cpp/include
pwd
cd ../src/python-bindings/pips
python3.8 -m pip install --upgrade pip
python3.8 -m pip install pybind11 twine
python3.8 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME

python3.9 -m pip install --upgrade pip
python3.9 -m pip install pybind11 twine
python3.9 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME

python3.10 -m pip install --upgrade pip
python3.10 -m pip install pybind11 twine
python3.10 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME