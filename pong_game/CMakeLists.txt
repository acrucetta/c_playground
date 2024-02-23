cmake_minimum_required(VERSION 3.0)
project(pong_game)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# Find raylib
find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

# Define the executable
add_executable(${PROJECT_NAME} main.c)

# Link with raylib
target_link_libraries(${PROJECT_NAME} raylib)
