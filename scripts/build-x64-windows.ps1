cd ./build/x64-windows
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="./vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_FIND_ROOT_PATH="./vcpkg/installed/x64-windows-static" -DVCPKG_TARGET_TRIPLET=x64-windows-static ../../
cmake --build . --config "Release"