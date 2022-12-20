FROM archlinux:latest
RUN pacman -Syyu --noconfirm \
    && pacman -S base-devel gcc qt6-base qt6-webengine cmake ninja python --noconfirm \
    && pacman -S python-pip --noconfirm \
    && pip install --upgrade pip \
    && pip install conan
WORKDIR /app
