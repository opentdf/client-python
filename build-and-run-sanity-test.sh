#!/usr/bin/env bash
ls -al
echo "Building python wrapper"
cd ../.. && ./build-all.sh

echo "Run the sanity test"
ls -al
PYV=$(python -c 'import sys; print("".join(map(str, sys.version_info[0:2])))')
unzip -l `find . -name \*.whl`
pip3 install `find . -name \*${PYV}*.whl` --force-reinstall
cd src/sample
python3 ./oidc-auth.py
