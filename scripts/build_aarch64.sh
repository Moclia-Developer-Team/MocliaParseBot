#!/usr/bin/env sh
echo "creating cmake cache"
cd ./build/aarch64
cmake -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release ../../
echo "build elf"
make -j20