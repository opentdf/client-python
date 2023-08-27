#!/bin/bash
set -ex

# This can be built two ways on mac: x86 binaries or M1 binaries
# It will check your system and Do The Right Thing

export OPENTDF_BUILD="build"
export OPENTDF_DST="opentdf-cpp"

rm -rf $OPENTDF_DST
rm -rf $OPENTDF_BUILD
mkdir $OPENTDF_BUILD
mkdir $OPENTDF_DST
mkdir $OPENTDF_DST/lib
mkdir $OPENTDF_DST/include

cd $OPENTDF_BUILD
conan --version
conan install .. --build=missing

# We should able to use cibuildwheel on windows and linux
cd ../src/python-bindings/pips
if [[ $OSTYPE == "darwin"* ]]; then
  export CIBW_ARCHS_MACOS="x86_64 arm64"
  export CIBW_SKIP="cp36-* cp12-*"
  python3 -m pip install --upgrade pip
  python3 -m pip install cibuildwheel --force
  cibuildwheel --platform macos
fi
