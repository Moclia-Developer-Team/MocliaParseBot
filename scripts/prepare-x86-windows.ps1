git clone https://github.com/microsoft/vcpkg.git .\vcpkg
git submodule init
git submodule update
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install cpr:x86-windows-static nlohmann-json:x86-windows-static fmt:x86-windows-static
mkdir build
mkdir ./build/x86-windows