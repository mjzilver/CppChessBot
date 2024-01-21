#include "gtest/gtest.h"
#include "../Pieces/Queen.h"
#include "../ChessBoard.h"
#include "../ChessPiece.h"

TEST(QueenTest, CanMoveTo) {
    Queen queen(4, 4, true); 

    // Test movement in a straight line
    EXPECT_TRUE(queen.canMoveTo(4, 7));
    EXPECT_TRUE(queen.canMoveTo(4, 1));
    EXPECT_TRUE(queen.canMoveTo(7, 4));
    EXPECT_TRUE(queen.canMoveTo(1, 4));

    // Test movement diagonally
    EXPECT_TRUE(queen.canMoveTo(7, 7));
    EXPECT_TRUE(queen.canMoveTo(1, 1));
    EXPECT_TRUE(queen.canMoveTo(7, 1));
    EXPECT_TRUE(queen.canMoveTo(1, 7));

    // Test invalid movement
    EXPECT_FALSE(queen.canMoveTo(5, 6));
    EXPECT_FALSE(queen.canMoveTo(3, 6));
    EXPECT_FALSE(queen.canMoveTo(5, 2));
    EXPECT_FALSE(queen.canMoveTo(3, 2));
}