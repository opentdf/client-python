#!/bin/bash
set -ex
export OPENTDF_BUILD="build"
export OPENTDF_DST="opentdf-cpp"
export WHEEL_OSX_PLAT_NAME="macosx_10_14_x86_64"

# Pin versions
export VER_WHEEL=0.38.4
export VER_PYBIND=2.10.3
export VER_TWINE=4.0.2

rm -rf $OPENTDF_DST
rm -rf $OPENTDF_BUILD
mkdir $OPENTDF_BUILD
mkdir $OPENTDF_DST
mkdir $OPENTDF_DST/lib
mkdir $OPENTDF_DST/include

cd $OPENTDF_BUILD

pip install pybind11 conan==1.59.0

conan --version
conan install "$GITHUB_WORKSPACE" --build=missing