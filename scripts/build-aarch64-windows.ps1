cd ./build/aarch64-windows
cmake -G "Visual Studio 16 2019" -A arm64  -DCMAKE_TOOLCHAIN_FILE="../../cmakeBuild/crossBuild-aarch64-windows.cmake" ../../
cmake --build . --config "Release" --target "MocliaParseBot"