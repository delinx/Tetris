cmake_minimum_required(VERSION 3.13)  # CMake version check
project(Tetris)               # Create project "Tetris"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

set(CMAKE_CXX_FLAGS "-fstack-protector -Wdeprecated -Wunused-parameter -ffunction-sections -fdata-sections -fno-common -Wconversion -Wall -Wextra -Wformat=2 -Wundef -Werror -Wshadow -Wdouble-promotion -g3 -O0 -pedantic -fcolor-diagnostics -Wno-unused-variable -Wno-unused-parameter -fsanitize=address -fno-omit-frame-pointer")

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(Tetris ${SOURCE_FILES})
