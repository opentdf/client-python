#!/bin/bash
set -e -x

# Install a system package required by our library
yum install -y centos-release-scl devtoolset-9 rh-python38-python-devel scl-utils wget

source /opt/rh/devtoolset-9/enable
source /opt/rh/rh-python38/enable
export PATH=$PATH:/opt/_internal/tools/bin

pip install --upgrade pip
pip install --upgrade cmake setuptools ninja scikit-build pybind11
pip install conan

/bin/bash
./io/build-all.sh
./io/build_wheels.sh
