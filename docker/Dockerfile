FROM ubuntu:22.04
RUN apt update \
    && apt -y upgrade \
    && apt -y install qt6-base-dev build-essential g++ wget ninja-build
WORKDIR /usr/local/cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.25.1/cmake-3.25.1-linux-x86_64.sh \
    && chmod +x cmake-3.25.1-linux-x86_64.sh \
    && ./cmake-3.25.1-linux-x86_64.sh --skip-license \
    && ln -s /usr/local/cmake/bin/cmake /usr/local/bin
RUN apt -y install libgl1-mesa-dev qt6-webengine-dev libxkbcommon-dev libvulkan-dev
WORKDIR /app
