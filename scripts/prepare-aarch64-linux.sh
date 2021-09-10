#!/usr/bin/env sh
echo "preparing build system"
sudo apt update
sudo apt install -y binutils-aarch64-linux-gnu gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
echo "preparing vcpkg"
sudo chmod 777 ~/vcpkg/vcpkg
~/vcpkg/vcpkg install cpr:arm64-linux nlohmann-json:arm64-linux fmt:arm64-linux 
echo "init submodule"
git submodule init
git submodule update
echo "creating folder"
mkdir build
mkdir ./build/aarch64-linux