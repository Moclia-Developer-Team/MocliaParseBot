#!/usr/bin/env sh
echo "creating cmake cache"
cd ./build/x86-linux
cmake -DCMAKE_TOOLCHAIN_FILE=../../cmakeBuild/crossBuild-x86-linux.cmake ../../
echo "build elf"
make -j20