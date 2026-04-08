@echo off

:: Create build directory and navigate into it
if not exist "build" mkdir build
cd build

:: Configure with CMake
cmake -DCMAKE_BUILD_TYPE=Debug ..

:: Build the project
cmake --build .