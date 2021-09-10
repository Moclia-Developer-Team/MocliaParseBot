# 必要，设置目标平台系统名称
SET(CMAKE_SYSTEM_NAME Windows)

# 设置交叉编译器
#SET(CMAKE_C_COMPILER /bin/gcc)
#SET(CMAKE_CXX_COMPILER /bin/g++)

# 设置编译平台
SET(CMAKE_BUILD_TYPE Release)

# 使用vcpkg
SET(CMAKE_TOOLCHAIN_FILE ~/vcpkg/scripts/buildsystems/vcpkg.cmake)

SET(VCPKG_TARGET_TRIPLET arm-windows-static)

# 设置查找位置
SET(CMAKE_FIND_ROOT_PATH ~/vcpkg/installed/arm-windows-static)

# 设置仅查找
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)