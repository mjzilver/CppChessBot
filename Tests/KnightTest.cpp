#include "gtest/gtest.h"
#include "../Pieces/Knight.h"
#include "../ChessBoard.h"
#include "../ChessPiece.h"

TEST(KnightTest, CanMoveTo) {
    ChessBoard board;
    Knight* knight = new Knight(4, 4, true); 
    board.addPiece(knight);

    // Test movement in an L shape
    EXPECT_TRUE(knight->canMoveTo(5, 6, &board));
    EXPECT_TRUE(knight->canMoveTo(3, 6, &board));
    EXPECT_TRUE(knight->canMoveTo(5, 2, &board));
    EXPECT_TRUE(knight->canMoveTo(3, 2, &board));
    EXPECT_TRUE(knight->canMoveTo(6, 5, &board));
    EXPECT_TRUE(knight->canMoveTo(6, 3, &board));
    EXPECT_TRUE(knight->canMoveTo(2, 5, &board));
    EXPECT_TRUE(knight->canMoveTo(2, 3, &board));

    // Test invalid movement
    EXPECT_FALSE(knight->canMoveTo(4, 5, &board));
    EXPECT_FALSE(knight->canMoveTo(4, 3, &board));
    EXPECT_FALSE(knight->canMoveTo(5, 4, &board));
    EXPECT_FALSE(knight->canMoveTo(3, 4, &board));
    // cant move to same spot
    EXPECT_FALSE(knight->canMoveTo(4, 4, &board));
}