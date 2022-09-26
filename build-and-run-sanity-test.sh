#!/usr/bin/env bash
ls -al
echo "Building python wrapper"
cd ../.. && ./build-all.sh

echo "Run the sanity test"
python -V
unzip -l `find . -name \*.whl`
pip3 install `find . -name \*.whl` --force-reinstall
cd src/sample
python3 ./oidc-auth.py
