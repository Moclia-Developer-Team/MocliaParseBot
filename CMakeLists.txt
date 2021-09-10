# CMake 版本要求 (最低 3.1)
cmake_minimum_required (VERSION 3.1)
# 项目名称（建议修改）
project(MocliaParseBot)
# 设置项目的 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 设置windows下的静态编译
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif(MSVC)

# 不要构建 mirai-cpp 自带的 examples
set(MIRAI_CPP_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
# 添加子模块 mirai-cpp
add_subdirectory(mirai-cpp)

find_package(cpr)
# find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json)

# 源码以 UTF-8 编码保存，使用 MSVC 编译器时需要加编译参数提供支持
if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    message(STATUS "optional: /UTF-8")   
endif(MSVC)

# 递归搜索 src 目录中的源文件
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# 设置头文件目录
include_directories(include)
# 链接 mirai-cpp
target_link_libraries(${PROJECT_NAME} PRIVATE mirai-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr)
# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

# 使用 mirai-cpp 静态库
target_compile_definitions(${PROJECT_NAME} PRIVATE MIRAICPP_STATICLIB)

if(MSVC)
target_compile_definitions(${PROJECT_NAME} PRIVATE _HAS_STD_BYTE=0)
endif(MSVC)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # 链接 pthread
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
    # 静态链接 libgcc 和 libstdc++
    target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()
