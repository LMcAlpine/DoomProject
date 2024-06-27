cmake_minimum_required(VERSION 3.10)
project(DoomProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)


# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/DoomGame)
include_directories(${PROJECT_SOURCE_DIR}/DoomGameTests)

# Source files
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/DoomGame/*.cpp")
set(TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/DoomGameTests/pch.cpp
    ${PROJECT_SOURCE_DIR}/DoomGameTests/WADReaderTests.cpp
)

# Add executable
add_executable(DoomProject ${SOURCES})

# Link SDL2
target_link_libraries(DoomProject ${SDL2_LIBRARIES})

# Ensure TEST_SOURCES is not empty
if(TEST_SOURCES)
  add_executable(DoomProjectTests ${TEST_SOURCES})

  # Google Test
  enable_testing()
  add_subdirectory(googletest)
  include_directories(googletest/googletest/include)
  target_link_libraries(DoomProjectTests gtest gtest_main ${SDL2_LIBRARIES})
  add_test(NAME DoomProjectTests COMMAND DoomProjectTests)
else()
  message(FATAL_ERROR "No test source files found in DoomGameTests directory")
endif()
