# 必要，设置目标平台系统名称
SET(CMAKE_SYSTEM_NAME Linux)

# 设置交叉编译器
SET(CMAKE_C_COMPILER /bin/aarch64-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER /bin/aarch64-linux-gnu-g++)

# 设置编译平台
SET(CMAKE_BUILD_TYPE Release)

# 使用vcpkg
SET(CMAKE_TOOLCHAIN_FILE ~/vcpkg/scripts/buildsystems/vcpkg.cmake)

# 设置查找位置
SET(CMAKE_FIND_ROOT_PATH ~/vcpkg/installed/arm64-linux)

# 设置仅查找
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

