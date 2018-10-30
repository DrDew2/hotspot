FROM ubuntu:bionic

RUN apt-get update && \
    apt-get install -y \
    build-essential git libkf5threadweaver-dev libkf5i18n-dev libkf5configwidgets-dev \
    libkf5coreaddons-dev libkf5itemviews-dev libkf5itemmodels-dev libkf5kio-dev \
    libkf5solid-dev libkf5windowsystem-dev libelf-dev libdw-dev cmake \
    extra-cmake-modules gettext qt5-default

WORKDIR /hotspot
RUN git clone --recurse-submodules https://github.com/KDAB/hotspot.git . && \
    mkdir build && \
    cd build && \
    cmake ../ && \
    make -j

RUN useradd -G video -ms /bin/bash user
USER user

WORKDIR /hotspot
CMD ["./build/bin/hotspot"]
