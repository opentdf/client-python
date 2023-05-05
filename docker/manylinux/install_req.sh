#!/bin/bash
set -e -x

# Install a system package required by our library
yum install -y centos-release-scl devtoolset-7 rh-python36-python-devel scl-utils wget 

source /opt/rh/devtoolset-7/enable
source /opt/rh/rh-python36/enable

pip install --upgrade pip
pip install --upgrade cmake setuptools ninja scikit-build pybind11
pip install --user conan

# install golang
wget -c https://storage.googleapis.com/golang/go1.13.linux-amd64.tar.gz
tar -C /usr/local -xzf go1.13.linux-amd64.tar.gz
export PATH=$PATH:/usr/local/go/bin

./build-all.sh
./docker/manylinux/build_wheels.sh
