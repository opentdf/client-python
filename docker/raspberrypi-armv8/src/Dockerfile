FROM balenalib/raspberrypi4-64:buster-build

LABEL vendor="Virtru Corporation"

# build-essential for cmake/make
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  cmake=3.16.3-3~bpo10+1 \
  wget=1.20.1-1.1 \
  git=1:2.20.1-2+deb10u3 \
  gnuplot=5.2.6+dfsg1-1+deb10u1 \
  python3-dev=3.7.3-1 \
  python3-pip=18.1-5+rpt1 \
  python3-venv=3.7.3-1 \
  python3-setuptools=40.8.0-1 \
  swig=3.0.12-2 \
  && rm -rf /var/lib/apt/lists/*

# install conan
RUN pip3 install --no-cache-dir wheel==0.32.3
RUN pip3 install --user --no-cache-dir conan==1.45.0 virtualenv==20.4.6

# install golang
RUN wget --progress=dot:giga -c https://dl.google.com/go/go1.13.10.linux-arm64.tar.gz
RUN tar -C /usr/local -xzf go1.13.10.linux-arm64.tar.gz
RUN export PATH=$PATH:/usr/local/go/bin
