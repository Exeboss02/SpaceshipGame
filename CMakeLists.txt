cmake_minimum_required(VERSION 3.10.0)
project(SpaceshipGame VERSION 0.1.0 LANGUAGES CXX)
cmake_policy(SET CMP0072 NEW)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(SpaceshipGame ${SOURCES})

# Include directories
target_include_directories(SpaceshipGame PRIVATE
    ${CMAKE_SOURCE_DIR}/raylib5.5/include
    ${CMAKE_SOURCE_DIR}/headers
)

# Link libraries (use the full path to raylib, without .lib extension)
target_link_libraries(SpaceshipGame PRIVATE
    "${CMAKE_SOURCE_DIR}/raylib5.5/lib/raylib.lib"
    winmm
    gdi32
)