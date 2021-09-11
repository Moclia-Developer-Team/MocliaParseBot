cd ./build/x86-windows
cmake -G "Visual Studio 16 2019" -A x86 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="./vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_FIND_ROOT_PATH="./vcpkg/installed/x86-windows-static" -DVCPKG_TARGET_TRIPLET=x86-windows-static ../../
cmake --build . --config "Release"