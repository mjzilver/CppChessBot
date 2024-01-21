cmake_minimum_required(VERSION 3.12)
project(ConsoleChess)

set(CMAKE_CXX_STANDARD 17)

# Add the source files
set(SOURCE_FILES
    main.cpp
    ChessBoard.h
    ChessBoard.cpp
    ChessPiece.h
    Player.h
    Player.cpp
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
add_executable(ConsoleChess ${SOURCE_FILES})

# Add Google Test
add_subdirectory(googletest)

# Add test cpp file
add_executable(runUnitTests
    Tests/QueenTest.cpp
)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)

# Enable testing
enable_testing()

add_test(NAME runUnitTests COMMAND runUnitTests)
