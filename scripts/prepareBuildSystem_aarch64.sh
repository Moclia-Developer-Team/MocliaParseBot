#!/usr/bin/env sh
echo "preparing vcpkg"
~/vcpkg install cpr nlohmann-json fmt 

echo "creating folder"
mkdir build
mkdir ./build/aarch64