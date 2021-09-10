git clone https://github.com/microsoft/vcpkg.git .\vcpkg
git submodule init
git submodule update
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install cpr:arm-windows-static nlohmann-json:arm-windows-static fmt:arm-windows-static
mkdir build
mkdir ./build/arm-windows