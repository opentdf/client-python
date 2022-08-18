#!/usr/bin/env bash

echo "Building python wrapper"
cd ../.. && ./build-all.sh

echo "Run the sanity test"
pip3 install `find . -name \*.whl`
cd src/sample
python3 ./oidc-auth.py
