cd ./build/arm-windows
cmake -G "Visual Studio 16 2019" -A arm  -DCMAKE_TOOLCHAIN_FILE="../../cmakeBuild/crossBuild-arm-windows.cmake" ../../
cmake --build . --config "Release" --target "MocliaParseBot"