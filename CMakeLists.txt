cmake_minimum_required(VERSION 3.30)

project(Cmixed_Library)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES main.cpp)
set(INCLUDES test.ixx test.cpp zzj.hpp)

# Debug Pragram Output Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../debug")

# Release Pragram Output Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../release")

add_executable(test ${SOURCES} ${INCLUDES})