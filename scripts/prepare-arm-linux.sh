#!/usr/bin/env sh
echo "preparing build system"
sudo apt update
sudo apt install -y binutils-arm-linux-gnueabi binutils-arm-linux-gnueabihf binutils-arm-none-eabi gcc-arm-linux-gnueabi g++-arm-linux-gnueabi gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf gcc-arm-none-eabi g++-arm-none-eabi
echo "preparing vcpkg"
sudo chmod 777 ~/vcpkg/vcpkg
~/vcpkg/vcpkg install cpr:arm-linux nlohmann-json:arm-linux fmt:arm-linux 
echo "init submodule"
git submodule init
git submodule update
echo "creating folder"
mkdir build
mkdir ./build/arm-linux