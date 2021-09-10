git clone https://github.com/microsoft/vcpkg.git .\vcpkg
git submodule init
git submodule update
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install cpr:arm64-windows-static nlohmann-json:arm64-windows-static fmt:arm64-windows-static
mkdir build
mkdir ./build/aarch64-windows