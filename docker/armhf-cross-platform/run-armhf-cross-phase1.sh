#!/bin/bash

# enable debugging and also exit immediately if a command exits with error.
set -ex

# some constants
TAG_VERSION=1.1.4
CURRENT_DIR=$(pwd)
DOCKER_IMAGE=tdf-cpp/armhf-cross-phase1:${TAG_VERSION}

# NOTE: when upgrading to different version tag make sure update this script
# to remove the previous version image

# some debug logs
echo "Running the cross-compile ARM build for ${DOCKER_IMAGE}..."
echo "Current dir - ${CURRENT_DIR}..."

# check if docker image exists if not build one
if [[ "$(docker images -q ${DOCKER_IMAGE} 2> /dev/null)" == "" ]]; then
	echo "Info: building docker image  ${DOCKER_IMAGE}..."
	docker build -t ${DOCKER_IMAGE} docker/armhf-cross-platform/src/phase1
else
	echo "Info: Reusing existing docker image ${DOCKER_IMAGE}..."
fi

#BUILDKITE_DOCKER=${BUILDKITE:-false}

if [[ $BUILDKITE_DOCKER == "true" ]]; then
  source buildkite-scripts/mars/functions/aws.sh
  export VAULT_TOKEN=$(get_ssm_parameter_secret_by_name "/secret/common/buildkite_build_agent/buildkite_qa_vault_token" "us-west-2")
fi

# run the image
docker run --rm -ti \
	-v ${CURRENT_DIR}:/app \
	-v ~/.ssh:/root/.ssh \
	-w /app \
        -u 0:0 \
	-e PATH=/root/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/go/bin:/opt/pyenv/shims \
	-e BUILDKITE_BRANCH\
	-e BUILDKITE\
	-e BUILDKITE_DOCKER\
        -e AWS_ACCESS_KEY_ID\
        -e AWS_SECRET_ACCESS_KEY\
        -e AWS_SESSION_TOKEN\
        -e VAULT_TOKEN\
	${DOCKER_IMAGE} \
	./build-all.sh rpi4-phase1 armv7
