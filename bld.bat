#!/bin/bash

clear

# Create build directory and navigate into it
mkdir -p build
cd build

# Configure with CMake
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build .
