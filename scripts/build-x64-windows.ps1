cd ./build/x64-windows
cmake -G "Visual Studio 16 2019" -A x64  -DCMAKE_TOOLCHAIN_FILE="../../cmakeBuild/build-x64-windows.cmake" ../../
cmake --build . --config "Release" --target "MocliaParseBot"