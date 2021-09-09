#!/usr/bin/env sh
echo "preparing build system"
sudo apt update -y
sudo apt upgrade -y
sudo apt install -y binutils-aarch64-linux-gnu gcc-aarch64-linux-gnu g++-aarch64-linux-gnu libssl-dev git ninja-build
echo "building cmake"
wget https://github.com/Kitware/CMake/releases/download/v3.21.2/cmake-3.21.2.tar.gz
tar -zxvf cmake-3.21.2.tar.gz
cd cmake-3.21.2
./configure
make -j20
sudo make install
echo "preparing vcpkg"
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh
~/vcpkg install cpr:arm64-linux nlohmann-json:arm64-linux fmt:arm64-linux 

echo "creating folder"
cd ..
mkdir build
mkdir ./build/aarch64