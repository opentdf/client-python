#!/bin/bash
rm -rf build
mkdir build
cd build
conan install .. --build=missing
conan install .. --build=missing
conan build .. -bf .
cd ..
