#!/usr/bin/env sh
echo "creating cmake cache"
cd ./build/arm-linux
cmake -DCMAKE_TOOLCHAIN_FILE=../../cmakeBuild/crossBuild-arm-linux.cmake ../../
echo "build elf"
make -j20