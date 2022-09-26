#!/bin/bash
set -e

# download all wheels using unix and win paths
mkdir -p dist
buildkite-agent artifact download "dist/opentdf*.whl" ./ || true
# download wheels not moved to dist/
mkdir -p tmp
buildkite-agent artifact download "src/**/opentdf*.whl" tmp/ || true
# download windows artifacts
buildkite-agent artifact download "src\**\opentdf*.whl" tmp/ || true
# list all in tmp
ls -R "${BUILDKITE_BUILD_CHECKOUT_PATH:-${PWD}}/tmp"
# move
mv tmp/src/python-bindings/pips/dist/*.whl dist/ || true
# list all in dist
ls -R "${BUILDKITE_BUILD_CHECKOUT_PATH:-${PWD}}/dist"

# PYPI_USER from pipeline.yml, PYPI_PASS from build env or common SSM parameter store
if [[ -z ${PYPI_PASS} ]]; then
  PYPI_PASS=$(aws ssm get-parameter --region us-west-2 --with-decryption --output text --query "Parameter.Value" --name "/secret/common/buildkite_build_agent/pypi_opentdf_password")
  echo "Retrieved PYPI password from SSM"
else
  echo "Using PYPI password supplied via environment variable"
fi

# create image with twine and twine command, run image/cmd with dist/ mapped
docker run --rm \
  -v "${BUILDKITE_BUILD_CHECKOUT_PATH:-${PWD}}/dist":/build/dist/ \
  -e PYPI_USER="${PYPI_USER}" \
  -e PYPI_PASS="${PYPI_PASS}" \
  $(docker build --quiet -<<EOF
    FROM python:3
    WORKDIR /build
    RUN mkdir -p dist
    RUN pip install twine
    ENV PYPI_USER=${PYPI_USER}
    CMD ls -R && twine upload --verbose --skip-existing dist/*.whl --username ${PYPI_USER} --password ${PYPI_PASS}
EOF
)
