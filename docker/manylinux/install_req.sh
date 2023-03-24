#!/bin/bash
set -e -x

# Pin versions
export VER_CMAKE=3.26.1
export VER_CENTOS_RELEASE_SCL=0:2-3.el7.centos
export VER_CONAN=1.59.0
export VER_DEVTOOLSET=0:9.1-0.el7
export VER_NINJA=1.11.1
export VER_PYBIND=2.10.3
export VER_PYTHON_DEVEL=0:3.8.13-1.el7
export VER_SCIKIT=0.16.7
export VER_SCL_UTILS=20130529-19.el7.x86_64
export VER_SETUPTOOLS=41.6.0-7.el7.noarch
export VER_WGET=0:1.14-18.el7_6.1

# Install a system package required by our library
yum install -y centos-release-scl-$VER_CENTOS_RELEASE_SCL devtoolset-9-$VER_DEVTOOLSET rh-python38-python-devel-$VER_PYTHON_DEVEL scl-utils-$VER_SCL_UTILS wget-$VER_WGET

source /opt/rh/devtoolset-9/enable
source /opt/rh/rh-python38/enable
export PATH=$PATH:/opt/_internal/tools/bin

pip install --upgrade pip

pip install cmake==$VER_CMAKE setuptools==$VER_SETUPTOOLS ninja==$VER_NINJA scikit-build==$VER_SCIKIT pybind11==$VER_PYBIND --force

pip install conan==$VER_CONAN --force

./build-all.sh
./docker/manylinux/build_wheels.sh
