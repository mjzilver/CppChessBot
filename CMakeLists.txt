cmake_minimum_required(VERSION 3.12)

project(CppChess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
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

# SFML Setup using FetchContent
include(FetchContent)

# Fetch SFML 2.6.1 and build it
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

FetchContent_MakeAvailable(SFML)

# Boost setup
find_package(Boost REQUIRED COMPONENTS thread system)
target_include_directories(CppChess PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(CppChess PRIVATE Boost::thread Boost::system)

# Link SFML to the executable
target_link_libraries(CppChess PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy images & font to the output directory
add_custom_command(
    TARGET CppChess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:CppChess>/resources
)
