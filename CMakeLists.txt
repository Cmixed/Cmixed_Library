cmake_minimum_required(VERSION 3.10)

project(Cpp20)

set(CMAKE_CXX_STANDARD 20)

# Debug Pragram Output Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../debug")
 
# Release Pragram Output Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../release")

add_executable(main main.cpp zzj.hpp)
