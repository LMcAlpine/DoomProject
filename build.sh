#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define build directory
BUILD_DIR="build"

# Remove the previous build directory
if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi

# Create a new build directory
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

# Run CMake to configure the project
cmake ..

# Build the project
make

cp ../DOOM.WAD .
cp ../mytestmap.wad .


# Run tests
ctest

echo "Build and tests completed successfully."
