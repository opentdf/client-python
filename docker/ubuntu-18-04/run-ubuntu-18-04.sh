#!/bin/bash

# enable debugging and also exit immediately if a command exits with error.
set -ex

# some constants
TAG_VERSION=1.0.11
CURRENT_DIR=$(pwd)
DOCKER_IMAGE=tdf-cpp/ubuntu-18.04:${TAG_VERSION}

# NOTE: when upgrading to different version tag make sure update this script
# to remove the previous version image

# some debug logs
echo "Running the linux build for ${DOCKER_IMAGE}..."
echo "Current dir - ${CURRENT_DIR}..."

# check if docker image exists if not build one
if [[ "$(docker images -q ${DOCKER_IMAGE} 2> /dev/null)" == "" ]]; then
	echo "Info: building docker image  ${DOCKER_IMAGE}..."
	docker build -t ${DOCKER_IMAGE} docker/ubuntu-18-04/src/.
else
	echo "Info: Reusing existing docker image ${DOCKER_IMAGE}..."
fi

if [[ $BUILDKITE == "true" ]]; then
  echo "Info: Getting vault token"
  source buildkite-scripts/mars/functions/aws.sh
  source buildkite-scripts/utils/logging.sh
  set +x
  export VAULT_TOKEN=$(get_ssm_parameter_secret_by_name "/secret/common/buildkite_build_agent/buildkite_qa_vault_token" "us-west-2")
  set -x
fi

if [ -z ${VAULT_TOKEN+x} ]; then
	echo "Failed to get Vault token, E2E tests will not run"
fi

# run the image
docker run --rm -ti \
	-v ${CURRENT_DIR}:/app \
	-w /app \
	-e PATH=/root/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/go/bin \
	-e BUILDKITE_BRANCH=${BUILDKITE_BRANCH} \
	-e VIRTRU_RUN_E2E_TESTS=${VIRTRU_RUN_E2E_TESTS} \
	-e BUILDKITE=${BUILDKITE} \
	-e BUILDKITE_DOCKER=${BUILDKITE_DOCKER} \
	-e VAULT_TOKEN \
	${DOCKER_IMAGE} \
	./build-all.sh
