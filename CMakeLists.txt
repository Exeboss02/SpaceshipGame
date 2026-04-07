cmake_minimum_required(VERSION 3.10.0)
project(SpaceshipGame VERSION 0.1.0 LANGUAGES CXX)
cmake_policy(SET CMP0072 NEW)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(SpaceshipGame ${SOURCES})

# Include directories (adjust if raylib is not in a standard location)
target_include_directories(SpaceshipGame PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    "C:/raylib/include"  # Path to raylib include directory
)

# Link directories (adjust if raylib is not in a standard location)
target_link_directories(SpaceshipGame PRIVATE
    "C:/raylib/lib"  # Path to raylib library directory
)

# Link libraries
target_link_libraries(SpaceshipGame
    raylib
    winmm  # Required for raylib on Windows
    gdi32  # Required for raylib on Windows
)