cmake_minimum_required(VERSION 3.20)

project(ServerBoost C CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/Binaries/mysql-connector/include)
include_directories(${CMAKE_SOURCE_DIR}/Binaries/mysql-connector/include/jdbc)
link_directories(${CMAKE_SOURCE_DIR}/Binaries/mysql-connector/lib64)

add_executable(ServerBoost src/main.cpp)
add_executable(TestServerBoost test/test_main.cpp)
target_link_libraries(ServerBoost ${CONAN_LIBS} mysqlcppconn)
target_link_libraries(TestServerBoost ${CONAN_LIBS} mysqlcppconn)
