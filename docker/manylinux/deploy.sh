#!/bin/bash

set -x

# manylinux build
echo "Building manylinux wheels with auditwheel and docker"
PLAT=manylinux2010_x86_64
DOCKER_IMAGE=quay.io/pypa/$PLAT

# Note that ALL non-fips tests fail to build on manylinux (and have for some time apparently), so we're turning them off
docker pull $DOCKER_IMAGE
docker run --rm \
   -v `pwd`:/io \
   -w /io \
   -e PATH=/root/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin \
   -e PLAT=$PLAT \
   $DOCKER_IMAGE \
   ./docker/manylinux/install_req.sh
