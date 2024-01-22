#include "../ChessBoard.h"
#include "../ChessPiece.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Rook.h"
#include "gtest/gtest.h"

TEST(RookTest, CanMoveTo) {
    ChessBoard board;
    Rook* rook = new Rook(4, 4, true);
    board.addPiece(rook);

    // Test movement in a straight line
    EXPECT_TRUE(rook->canMoveTo(4, 7, &board));
    EXPECT_TRUE(rook->canMoveTo(4, 1, &board));
    EXPECT_TRUE(rook->canMoveTo(7, 4, &board));
    EXPECT_TRUE(rook->canMoveTo(1, 4, &board));

    // Test invalid movement
    EXPECT_FALSE(rook->canMoveTo(5, 6, &board));
    EXPECT_FALSE(rook->canMoveTo(3, 6, &board));
    EXPECT_FALSE(rook->canMoveTo(5, 2, &board));
    EXPECT_FALSE(rook->canMoveTo(3, 2, &board));
}

TEST(RookTest, CanMoveToBlocked) {
    ChessBoard board;
    Rook* rook = new Rook(4, 4, true);
    board.addPiece(rook);

    // Test movement in a straight line
    board.addPiece(new Pawn(4, 5, true));
    EXPECT_FALSE(rook->canMoveTo(4, 7, &board));
    board.emptyBoard();
}