#!/bin/bash
set -e -x

# Install a system package required by our library
yum install -y centos-release-scl devtoolset-9 rh-python38-python-devel scl-utils wget

source /opt/rh/devtoolset-9/enable
source /opt/rh/rh-python38/enable
export PATH=$PATH:/opt/_internal/tools/bin
export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/usr/local/lib64:/usr/lib64
strings libstdc++.so.6.0.28 | grep GLIBCXX

pip install --upgrade pip
pip install --upgrade cmake setuptools ninja scikit-build pybind11
pip install conan==1.52.0

./build-all.sh
./docker/manylinux_aarch64/build_wheels.sh
