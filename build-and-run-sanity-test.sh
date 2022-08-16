#!/usr/bin/env bash

echo "Building python wrapper"
cd ../.. && ./build-all.sh

echo "Run the sanity test"
cd src/sample
python3 ./oidc-auth.py
