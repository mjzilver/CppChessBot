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

# Windows-specific settings
if(WIN32)
    set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")
    set(SFML_DIR "C:/Program Files/SFML-2.6.1/lib/cmake/SFML")
endif()

# Source files
set(SOURCE_FILES
    main.cpp
    ChessBoard.h
    ChessBoard.cpp
    AI/AI.h
    AI/AI.cpp
    UI/GDisplay.h
    UI/GDisplay.cpp
    UI/ConsoleDisplay.h
    UI/ConsoleDisplay.cpp
    ChessGame.h
    ChessGame.cpp
)

# Create the executable
add_executable(CppChess ${SOURCE_FILES})

# Find SFML
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Link SFML to the executable
target_link_libraries(CppChess sfml-graphics sfml-window sfml-system)
