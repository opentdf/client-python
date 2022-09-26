#!/bin/bash

# enable debugging and also exit immediately if a command exits with error.
set -ex

# some constants
TAG_VERSION=1.1.2
CURRENT_DIR=$(pwd)
DOCKER_IMAGE=tdf-cpp/pi-4-armv7-phase2:${TAG_VERSION}

# NOTE: when upgrading to different version tag make sure update this script
# to remove the previous version image

# some debug logs
echo "Running the raspberry pi build for ${DOCKER_IMAGE}..."
echo "Current dir - ${CURRENT_DIR}..."

# check if docker image exists if not build one
if [[ "$(docker images -q ${DOCKER_IMAGE} 2> /dev/null)" == "" ]]; then
	echo "Info: building docker image  ${DOCKER_IMAGE}..."
	docker build --platform linux/arm/v7 -t ${DOCKER_IMAGE} docker/armhf-cross-platform/src/phase2
else
	echo "Info: Reusing existing docker image ${DOCKER_IMAGE}..."
fi

# Copy phase1 results in
cd ${CURRENT_DIR}
buildkite-agent artifact download "phase1.tar.gz" ./
mkdir -p src/build 
cd src/build
pwd
tar xvf ${CURRENT_DIR}/phase1.tar.gz
cd ${CURRENT_DIR}

# run the image
docker run --rm -ti \
	-v ${CURRENT_DIR}:/app \
	-w /app \
	-e PATH=/root/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/go/bin \
	-e BUILDKITE_BRANCH\
	-e BUILDKITE\
	-e BUILDKITE_BUILD_NUMBER\
	-e PLAT\
	${DOCKER_IMAGE} \
	./build-all.sh rpi4-phase2 armv7
