#!/bin/bash


# enable debugging and also exit immediately if a command exits with error.
set -ex

# some constants
TAG_VERSION=1.0.6
CURRENT_DIR=$(pwd)
DOCKER_IMAGE=tdf-cpp/pi-armv8:${TAG_VERSION}

# NOTE: when upgrading to different version tag make sure update this script
# to remove the previous version image

# some debug logs
echo "Running the raspberrypi-4 build for ${DOCKER_IMAGE}..."
echo "Current dir - ${CURRENT_DIR}..."

# check if docker image exists if not build one
if [[ "$(docker images -q ${DOCKER_IMAGE} 2> /dev/null)" == "" ]]; then
	echo "Info: building docker image  ${DOCKER_IMAGE}..."
	cp ./src/conanfile.py docker/raspberrypi-armv8/src/
	docker build -t ${DOCKER_IMAGE} docker/raspberrypi-armv8/src/.
else
	echo "Info: Reusing existing docker image ${DOCKER_IMAGE}..."
fi


# run the image
docker run --rm -ti \
	-v ${CURRENT_DIR}:/app \
	-w /app \
	-e PATH=/root/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/go/bin \
	-e BUILDKITE_BRANCH=${BUILDKITE_BRANCH} \
	-e BUILDKITE=${BUILDKITE} \
	-e BUILDKITE_BUILD_NUMBER=${BUILDKITE_BUILD_NUMBER} \
	-e PLAT=$PLAT \
	${DOCKER_IMAGE} \
	./build-all.sh rpi4 armv8
