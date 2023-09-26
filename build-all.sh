#!/bin/bash
set -ex

# This can be built two ways on mac: x86 binaries or M1 binaries
# It will check your system and Do The Right Thing

export OPENTDF_BUILD="build"
export OPENTDF_DST="opentdf-cpp"

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


cd $OPENTDF_BUILD
conan --version
conan install .. --build=missing
conan build .. --build-folder .

#conan build .. --build-folder .

# We should able to use cibuildwheel on windows and linux
# cd ../src/python-bindings/pips
# if [[ $OSTYPE == "darwin"* ]]; then
#   export CIBW_ARCHS_MACOS="x86_64"
#   export CIBW_SKIP="cp36-* cp12-*"
#   python3 -m pip install --upgrade pip
#   python3 -m pip install cibuildwheel --force
#   cibuildwheel --platform macos
# fi


cd ../src/python-bindings/pips
if [[ $OSTYPE == "darwin"* ]]; then
  # python3 -m pip install --upgrade pip
  # python3 -m pip install wheel==$VER_WHEEL pybind11==$VER_PYBIND twine==$VER_TWINE --force
  # python3 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME

  export PATH="/opt/homebrew/Cellar/python@3.8/3.8.16/bin:$PATH"
  python3.8 -m pip install --upgrade pip
  python3.8 -m pip install pybind11 twine
  python3.8 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME

  export PATH="/opt/homebrew/Cellar/python@3.9/3.9.16/bin:$PATH"
  python3.9 -m pip install --upgrade pip
  python3.9 -m pip install pybind11 twine
  python3.9 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME

  export PATH="//opt/homebrew/Cellar/python@3.10/3.10.10_1/bin:$PATH"
  python3.10 -m pip install --upgrade pip
  python3.10 -m pip install pybind11 twine
  python3.10 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME

  export PATH="/opt/homebrew/Cellar/python@3.11/3.11.2_1/bin:$PATH"
  python3.11 -m pip install --upgrade pip
  python3.11 -m pip install pybind11 twine
  python3.11 setup.py bdist_wheel --plat-name $WHEEL_OSX_PLAT_NAME
fi

