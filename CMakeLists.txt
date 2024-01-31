cmake_minimum_required(VERSION 3.12)
project(CppChess)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# if windows
if(WIN32)
    # Set the C compiler
    set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
    # Set the C++ compiler
    set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")
    # build for mingw 
    set(CMAKE_GENERATOR "MinGW Makefiles")
endif()

# Add the source files
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

# if win
if(WIN32)
    # set the path to the SFML libraries
    set(SFML_DIR "C:/Program Files/SFML-2.6.1/lib/cmake/SFML")
endif()
find_package(SFML COMPONENTS graphics REQUIRED)

# link SFML to main executable
target_link_libraries(CppChess sfml-graphics sfml-window sfml-system)
