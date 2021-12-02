cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE tools/cmake/ArduinoToolchain.cmake)

project(rollercoaster C CXX)

add_subdirectory(node/Software/lib)
add_subdirectory(tools)
add_subdirectory(rollercoaster)
