cmake_minimum_required(VERSION 3.10)
project(VectorProject C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wunused-variable")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Always export compile_commands.json (no more -DC flag)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include library headers and Unity headers
include_directories(include tests/Unity)

# Library sources
file(GLOB_RECURSE LIB_SOURCES "src/*.c")
add_library(MyLibrary STATIC ${LIB_SOURCES})

# Enable testing
enable_testing()
add_subdirectory(tests)

# Optional: symlink compile_commands.json to project root (for clangd/LSP)
add_custom_target(copy_compile_commands ALL
				COMMAND ${CMAKE_COMMAND} -E create_symlink
												${CMAKE_BINARY_DIR}/compile_commands.json
												${CMAKE_SOURCE_DIR}/compile_commands.json
				DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)
