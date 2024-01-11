cmake_minimum_required(VERSION 3.20)

project(ServerBoost C CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ServerBoost src/main.cpp)
target_link_libraries(ServerBoost ${CONAN_LIBS})
