#!/usr/bin/env sh
echo "creating cmake cache"
cd ./build/x64-linux
cmake -DCMAKE_TOOLCHAIN_FILE=../../cmakeBuild/build-x64-linux.cmake ../../
echo "build elf"
make -j20