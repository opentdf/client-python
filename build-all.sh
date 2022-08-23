#!/bin/bash
set -ex
rm -rf build
mkdir build
cd build
export VBUILD_UNIT_TESTS="false"
conan install .. --build=missing
conan build .. -bf .
cd ..
