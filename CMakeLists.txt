cmake_minimum_required(VERSION 3.10)
project(VectorProject C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include library headers and Unity headers
include_directories(include tests/Unity)

# Library sources
file(GLOB_RECURSE LIB_SOURCES "src/*.c")
add_library(MyLibrary STATIC ${LIB_SOURCES})

# Enable testing
enable_testing()
add_subdirectory(tests)

