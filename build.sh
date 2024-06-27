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
echo "Creating new build directory..."
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

# Run CMake to configure the project
cmake ..

# Build the project
make

cp ../DOOM.WAD .
cp ../mytestmap.wad .

# Set environment variables
export DOOM_WAD_PATH="$(pwd)/DOOM.WAD"
export MYTESTMAP_WAD_PATH="$(pwd)/mytestmap.wad"
export TEST_ENV="local"


echo "DOOM_WAD_PATH is set to $DOOM_WAD_PATH"
echo "MYTESTMAP_WAD_PATH is set to $MYTESTMAP_WAD_PATH"
echo "TEST_ENV is set to $TEST_ENV"


# Run tests
ctest

echo "Build and tests completed successfully."
