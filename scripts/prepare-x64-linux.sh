#!/usr/bin/env sh
echo "preparing vcpkg"
sudo chmod 777 ~/vcpkg/vcpkg
~/vcpkg/vcpkg install cpr:x64-linux nlohmann-json:x64-linux fmt:x64-linux 
echo "init submodule"
git submodule init
git submodule update
echo "creating folder"
mkdir build
mkdir ./build/x64-linux