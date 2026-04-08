cmake_minimum_required(VERSION 3.10.0)
project(SpaceshipGame VERSION 0.1.0 LANGUAGES CXX)
cmake_policy(SET CMP0072 NEW)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(SpaceshipGame ${SOURCES})

# Detect the operating system
if(WIN32)
    # Windows-specific settings
    message(STATUS "Configuring for Windows")
    target_include_directories(SpaceshipGame PRIVATE
        ${CMAKE_SOURCE_DIR}/raylib5.5_windows/include
    )
    target_link_libraries(SpaceshipGame PRIVATE
        "${CMAKE_SOURCE_DIR}/raylib5.5_windows/lib/raylib.lib"
        winmm
        gdi32
    )
elseif(UNIX AND NOT APPLE)
    # Linux-specific settings
    message(STATUS "Configuring for Linux")
    target_include_directories(SpaceshipGame PRIVATE
        ${CMAKE_SOURCE_DIR}/raylib5.5_linux/include
    )
    # Use static library
    target_link_libraries(SpaceshipGame PRIVATE
        "${CMAKE_SOURCE_DIR}/raylib5.5_linux/lib/libraylib.a"
    )
endif()