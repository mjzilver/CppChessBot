cmake_minimum_required(VERSION 3.12)
project(CppChess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Define build-specific flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall" CACHE STRING "Flags for debug builds")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall" CACHE STRING "Flags for release builds")
set(CMAKE_CXX_FLAGS_PROFILE "-O3 -pg -Wall" CACHE STRING "Flags for profiling builds")

# Source files
file(GLOB_RECURSE SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
)

# Create the executable
add_executable(CppChess ${SOURCE_FILES})

# Find SFML
find_package(SFML COMPONENTS graphics window system REQUIRED)

# If SFML is not found, throw an error
if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML was not found. Please make sure SFML is installed and available in your system's CMake module paths.")
endif()

# Link SFML to the executable
target_link_libraries(CppChess sfml-graphics sfml-window sfml-system)
