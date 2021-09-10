#!/usr/bin/env sh
echo "preparing build system"
sudo apt update
sudo apt install -y binutils-i686-linux-gnu gcc-i686-linux-gnu g++-i686-linux-gnu
echo "preparing vcpkg"
cp ./cmakeBuild/x86-linux.cmake ~/vcpkg/triplets/
~/vcpkg/bootstrap-vcpkg.sh
sudo chmod 777 ~/vcpkg/vcpkg
~/vcpkg/vcpkg install cpr:x86-linux nlohmann-json:x86-linux fmt:x86-linux 
echo "init submodule"
git submodule init
git submodule update
echo "creating folder"
mkdir build
mkdir ./build/x86-linux