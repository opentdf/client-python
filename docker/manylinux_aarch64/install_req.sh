#!/bin/bash
set -e -x

# Install a system package required by our library
yum install -y centos-release-scl devtoolset-9 rh-python38-python-devel python3-pip scl-utils wget 

source /opt/rh/devtoolset-9/enable
source /opt/rh/rh-python38/enable

pip3 install --upgrade pip
pip3 install --upgrade setuptools ninja scikit-build pybind11
pip3 install --user conan

./build-all.sh
./docker/manylinux_aarch64/build_wheels.sh
