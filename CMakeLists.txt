# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(KasiRun LANGUAGES CXX)

# Set the C++ standard to C++11 (or C++14, C++17, etc.)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the source files
add_executable(krun main.cpp)

# Find raylib package
find_package(raylib REQUIRED)

# Link raylib
target_link_libraries(krun raylib)

