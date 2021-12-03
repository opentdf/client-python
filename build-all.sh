#!/bin/bash
rm -rf build
mkdir build
cd build
conan install ..
conan build .. --build-folder .
cd ..
