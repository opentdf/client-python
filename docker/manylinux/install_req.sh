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

# Pre-load conan cache with build from local conan recipe instead of CCI to avoid having to wait for CCI review process
git clone https://github.com/opentdf/client-conan.git
cd client-conan
conan create recipe/all opentdf-client/$VCLIENT_CPP_VER@ -pr:b=default --build=opentdf-client --build=missing -o opentdf-client:branch_version=$VCONAN_BRANCH_VERSION
cd ..

./build-all.sh
./docker/manylinux/build_wheels.sh
