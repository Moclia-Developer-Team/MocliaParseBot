#!/usr/bin/env sh
echo "preparing vcpkg"
sudo chmod 777 ~/vcpkg/vcpkg
~/vcpkg/vcpkg install cpr nlohmann-json fmt 
echo "init submodule"
git submodule --init
git submodule update
echo "creating folder"
mkdir build
mkdir ./build/aarch64