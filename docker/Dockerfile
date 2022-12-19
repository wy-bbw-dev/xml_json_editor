FROM archlinux:latest
RUN pacman -Syyu --noconfirm \
    && pacman -S base-devel gcc qt6-base qt6-webengine cmake ninja --noconfirm
WORKDIR /app
