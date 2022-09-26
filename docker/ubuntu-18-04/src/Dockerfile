FROM ubuntu:18.04
LABEL vendor="Virtru Corporation"

# build-essential for cmake/make
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  build-essential=12.4ubuntu1 \
  valgrind=1:3.13.0-2ubuntu2.3 \
  cmake=3.10.2-1ubuntu2.18.04.2 \
  lcov=1.13-3 \
  html2text=1.3.2a-21 \
  git=1:2.17.1-1ubuntu0.12 \
  wget=1.19.4-1ubuntu2.2 \
  python3-pip=9.0.1-2.3~ubuntu1.18.04.5 \
  python3-setuptools=39.0.1-2 \
  python3-dev=3.6.7-1~18.04 \
  python3-venv=3.6.7-1~18.04 \
  netbase=5.4 \
  openjdk-8-jdk=8u312-b07-0ubuntu1~18.04 \ 
  maven=3.6.0-1~18.04.1 \
  curl=7.58.0-2ubuntu3.19 \
  jq=1.5+dfsg-2 \
  && rm -rf /var/lib/apt/lists/*

# install conan
RUN pip3 install --no-cache-dir --user conan==1.43.1

# install golang
RUN wget --progress=dot:giga -c https://storage.googleapis.com/golang/go1.13.linux-amd64.tar.gz
RUN tar -C /usr/local -xzf go1.13.linux-amd64.tar.gz
RUN export PATH=$PATH:/usr/local/go/bin
