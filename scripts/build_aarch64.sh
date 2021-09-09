#!/usr/bin/env sh
echo "creating cmake cache"
cd ./build/aarch64
cmake -DCMAKE_TOOLCHAIN_FILE=../../cmakeBuild/crossBuild-aarch64.cmake ../../
echo "build elf"
make -j20