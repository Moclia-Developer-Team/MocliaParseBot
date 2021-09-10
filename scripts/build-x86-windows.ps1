cd ./build/x86-windows
cmake -G "Visual Studio 16 2019" -A x86  -DCMAKE_TOOLCHAIN_FILE="../../cmakeBuild/build-x86-windows.cmake" ../../
cmake --build . --config "Release" --target "MocliaParseBot"