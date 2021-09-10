git clone https://github.com/microsoft/vcpkg.git .\vcpkg
git submodule init
git submodule update
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install cpr:x64-windows-static nlohmann-json:x64-windows-static fmt:x64-windows-static
mkdir build
mkdir ./build/x64-windows