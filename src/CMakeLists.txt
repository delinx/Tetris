cmake_minimum_required(VERSION 3.13)  # CMake version check
project(Tetris)               # Create project "Tetris"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard
set(CMAKE_C_STANDARD 99)

# Adding Raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

set(CMAKE_CXX_FLAGS "-fstack-protector -Wdeprecated -Wunused-parameter -ffunction-sections -fdata-sections -fno-common -Wconversion -Wall -Wextra -Wformat=2 -Werror -Wshadow -Wdouble-promotion -g3 -O0 -pedantic -fcolor-diagnostics -Wno-unused-variable -Wno-unused-parameter -fsanitize=address -fno-omit-frame-pointer")

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp log.cpp gfxhelper.cpp logic.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(Tetris ${SOURCE_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
