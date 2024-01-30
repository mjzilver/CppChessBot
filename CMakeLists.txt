cmake_minimum_required(VERSION 3.12)
project(CppChess)

set(CMAKE_CXX_STANDARD 17)

# if windows
if(WIN32)
    # Set the C compiler
    set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
    # Set the C++ compiler
    set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")
    # build for mingw and NOT visual studio
    set(CMAKE_GENERATOR "MinGW Makefiles")
endif()

# Add the source files
set(SOURCE_FILES
    main.cpp
    ChessBoard.h
    ChessBoard.cpp
    ChessPiece.h
    ChessPiece.cpp
    UI/GDisplay.h
    UI/GDisplay.cpp
    UI/ConsoleDisplay.h
    UI/ConsoleDisplay.cpp
    ChessGame.h
    ChessGame.cpp
    Pieces/Pawn.h
    Pieces/Rook.h
    Pieces/Knight.h
    Pieces/Bishop.h
    Pieces/Queen.h
    Pieces/King.h
)

# Create the executable
add_executable(CppChess ${SOURCE_FILES})

# Add Google Test
add_subdirectory(googletest)

# Add files to be included in testing
add_executable(runUnitTests
    ChessBoard.cpp
    ChessPiece.cpp
    Tests/QueenTest.cpp
    Tests/BishopTest.cpp
    Tests/KnightTest.cpp
    Tests/RookTest.cpp
    Tests/PawnTest.cpp
    Tests/KingTest.cpp
)

# if win
if(WIN32)
    # set the path to the SFML libraries
    set(SFML_DIR "C:/Program Files/SFML-2.6.1/lib/cmake/SFML")
endif()
find_package(SFML COMPONENTS graphics REQUIRED)

# link gtest to test executable
target_link_libraries(runUnitTests gtest gtest_main)
# link SFML to main executable
target_link_libraries(CppChess sfml-graphics sfml-window sfml-system)

# Enable testing
enable_testing()

add_test(NAME runUnitTests COMMAND runUnitTests)
