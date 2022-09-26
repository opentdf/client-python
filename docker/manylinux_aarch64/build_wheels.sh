#!/bin/bash
set -e -x

# Auditwheel requirements
yum install -y atlas-devel

yum install -y gsl-devel
yum install -y boost-devel

OUT_DIR=/io/src/python-bindings/pips/dist/

pys=(
    /opt/python/cp36-cp36m/bin/python
    /opt/python/cp37-cp37m/bin/python
    /opt/python/cp38-cp38/bin/python
    /opt/python/cp39-cp39/bin/python
    /opt/python/cp310-cp310/bin/python
)

mkdir -p "${OUT_DIR}"
for PYBIN in "${pys[@]}"; do
    # Setup
    TMP_DIR="wheelhouse_tmp/${PLAT}/${PYBIN}"
    REPAIR_DIR="wheelhouse_repair/${PLAT}/${PYBIN}"
    mkdir -p $TMP_DIR
    mkdir -p $REPAIR_DIR

    # Compile wheels
    cd /io/src/python-bindings/pips
    mkdir -p "opentdf"
    
    echo "from .opentdf import *" > opentdf/__init__.py
   
    "${PYBIN}" -m pip install pybind11 twine
    "${PYBIN}" setup.py bdist_wheel -d "${TMP_DIR}"

    # Bundle external shared libraries into the wheels
    for whl in $(ls -1 ${TMP_DIR}); do
      auditwheel show ${TMP_DIR}/$whl
      auditwheel repair --plat "$PLAT" -w "${REPAIR_DIR}" ${TMP_DIR}/$whl
    done

    find dist/ -type f  -name '*linux_aarch64.whl' -delete

    # Move wheel to output directory
    for whl in $(ls -1 ${REPAIR_DIR} | grep manylinux); do
      mv ${REPAIR_DIR}/$whl "${OUT_DIR}"
    done
   
done
