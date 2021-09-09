#!/usr/bin/env sh
echo "preparing build system"
sudo apt update -y
sudo apt upgrade -y

echo "preparing vcpkg"
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh
~/vcpkg install cpr:arm64-linux nlohmann-json:arm64-linux fmt:arm64-linux 

echo "creating folder"
cd ..
mkdir build
mkdir ./build/aarch64