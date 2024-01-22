cmake_minimum_required(VERSION 3.12)
project(ConsoleChess)

set(CMAKE_CXX_STANDARD 17)

# Add the source files
set(SOURCE_FILES
    main.cpp
    ChessBoard.h
    ChessBoard.cpp
    ChessPiece.h
    ChessGUI.h
    ChessGUI.cpp
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

# Add files to be included in testing
add_executable(runUnitTests
    ChessBoard.cpp
    Player.cpp
    Tests/QueenTest.cpp
    Tests/BishopTest.cpp
    Tests/KnightTest.cpp
    Tests/RookTest.cpp
    Tests/PawnTest.cpp
    Tests/KingTest.cpp
)

# link gtest to test executable
target_link_libraries(runUnitTests gtest gtest_main)
# link SFML to main executable
target_link_libraries(ConsoleChess sfml-graphics sfml-window sfml-system)

# Enable testing
enable_testing()

add_test(NAME runUnitTests COMMAND runUnitTests)
