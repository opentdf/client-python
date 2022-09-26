FROM conanio/gcc10@sha256:132853a6c58b5ec24c6171a62bfee60c3268a6e7f0bf6cdd980bc1f3db915d06
USER root

LABEL vendor="Virtru Corporation"
 
ENV CC=arm-linux-gnueabi-gcc-10 \
    CXX=arm-linux-gnueabi-g++-10 \
    CMAKE_C_COMPILER=arm-linux-gnueabi-gcc-10 \
    CMAKE_CXX_COMPILER=arm-linux-gnueabi-g++-10 \
    STRIP=arm-linux-gnueabi-strip \
    RANLIB=arm-linux-gnueabi-ranlib \
    AS=arm-linux-gnueabi-as \
    AR=arm-linux-gnueabi-ar \
    LD=arm-linux-gnueabi-ld \
    FC=arm-linux-gnueabi-gfortran-10

RUN apt-get -qq update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake=3.16.3-1ubuntu1 \
    netbase=6.1 \
    wget=1.20.3-1ubuntu1 \
    maven=3.6.3-1 \
    swig=4.0.1-5build1 \
    curl=7.68.0-1ubuntu2.7 \
    git=1:2.25.1-1ubuntu3.2 \
    openssh-client=1:8.2p1-4ubuntu0.4 \
    jq=1.6-1ubuntu0.20.04.1 \
    openjdk-8-jdk=8u312-b07-0ubuntu1~20.04 \
    ".*10.*arm-linux-gnueabi.*"=10.3.0-1ubuntu1~20.04cross1 \
    && update-alternatives --install /usr/bin/arm-linux-gnueabi-gcc arm-linux-gnueabi-gcc /usr/bin/arm-linux-gnueabi-gcc-10 100 \
    && update-alternatives --install /usr/bin/arm-linux-gnueabi-g++ arm-linux-gnueabi-g++ /usr/bin/arm-linux-gnueabi-g++-10 100 \
    && update-alternatives --install /usr/bin/arm-linux-gnueabi-gcov arm-linux-gnueabi-gcov /usr/bin/arm-linux-gnueabi-gcov-10 100 \
    && update-alternatives --install /usr/bin/arm-linux-gnueabi-gcov-dump arm-linux-gnueabi-gcov-dump /usr/bin/arm-linux-gnueabi-gcov-dump-10 100 \
    && update-alternatives --install /usr/bin/arm-linux-gnueabi-gcov-tool arm-linux-gnueabi-gcov-tool /usr/bin/arm-linux-gnueabi-gcov-tool-10 100 \
    && rm -rf /var/lib/apt/lists/* \
    && pip3 install --no-cache-dir -q conan==1.45.0 conan-package-tools==0.35.1

# install golang
RUN wget --progress=dot:giga -c https://dl.google.com/go/go1.16.linux-armv6l.tar.gz
RUN tar -C /usr/local -xzf go1.16.linux-armv6l.tar.gz
RUN export PATH=$PATH:/usr/local/go/bin:/root/.local/bin

WORKDIR /app
 
USER conan

