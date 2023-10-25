cmake_minimum_required(VERSION 3.0)

project(SPECIAL_LICENSE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

set(CMAKE_BUILD_TYPE Debug)

# 查找OpenSSL库
find_package(OpenSSL REQUIRED)

# 添加可执行文件
add_executable(license_hex.out license_hex.cpp)

# 添加OpenSSL库的头文件路径
target_include_directories(license_hex.out PRIVATE ${OPENSSL_INCLUDE_DIR})

# 将OpenSSL库链接到可执行文件中
target_link_libraries(license_hex.out PRIVATE ${OPENSSL_LIBRARIES})