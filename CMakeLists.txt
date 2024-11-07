cmake_minimum_required(VERSION 3.22)
project(GrowtopiaServer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin")

add_subdirectory(src)
add_subdirectory(vendor)