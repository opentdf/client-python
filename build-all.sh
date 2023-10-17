#!/bin/bash
set -ex

# This can be built two ways on mac: x86 binaries or M1 binaries
# It will check your system and Do The Right Thing

export OPENTDF_BUILD="build"
export OPENTDF_DST="opentdf-cpp"
ARCH=`uname -m`

# This naming contains the *MINIMUM* OS version supported, which may not be the one running currently
if [[ $OSTYPE == "darwin"* ]]; then
  if [[ `uname -m` == "arm64" ]]; then
    export WHEEL_OSX_PLAT_NAME="macosx_12_0_arm64"
  else
    export WHEEL_OSX_PLAT_NAME="macosx_10_14_x86_64"
  fi
fi

rm -rf $OPENTDF_DST
rm -rf $OPENTDF_BUILD
mkdir $OPENTDF_BUILD
mkdir $OPENTDF_DST
mkdir $OPENTDF_DST/lib
mkdir $OPENTDF_DST/include

cd $OPENTDF_BUILD
conan --version
conan install .. --build=missing
conan build .. --build-folder .


# # We should able to use cibuildwheel on windows and linux
cd ../src/python-bindings/pips
if [[ $OSTYPE == "darwin"* ]]; then
  export CIBW_ARCHS_MACOS=$ARCH
  export CIBW_SKIP="cp36-* cp12-*"
  python3 -m pip install --upgrade pip
  python3 -m pip install cibuildwheel --force
  cibuildwheel --platform macos
fi
