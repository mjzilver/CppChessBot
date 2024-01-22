#include "gtest/gtest.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Pawn.h"
#include "../ChessBoard.h"
#include "../ChessPiece.h"

TEST(BishopTest, CanMoveTo) {
    ChessBoard board;
    Bishop* bishop = new Bishop(4, 4, true); 
    board.addPiece(bishop);

    // Test movement diagonally
    EXPECT_TRUE(bishop->canMoveTo(7, 7, &board));
    EXPECT_TRUE(bishop->canMoveTo(1, 1, &board));
    EXPECT_TRUE(bishop->canMoveTo(7, 1, &board));
    EXPECT_TRUE(bishop->canMoveTo(1, 7, &board));

    // Test invalid movement
    EXPECT_FALSE(bishop->canMoveTo(5, 6, &board));
    EXPECT_FALSE(bishop->canMoveTo(3, 6, &board));
    EXPECT_FALSE(bishop->canMoveTo(5, 2, &board));
    EXPECT_FALSE(bishop->canMoveTo(3, 2, &board));
    EXPECT_FALSE(bishop->canMoveTo(4, 5, &board));
    // cant move to same spot
    EXPECT_FALSE(bishop->canMoveTo(4, 4, &board));
}

TEST(BishopTest, CanMoveToBlocked) {
    ChessBoard board;
    Bishop* bishop = new Bishop(4, 4, true); 
    board.addPiece(bishop);

    // Test movement diagonally
    board.addPiece(new Pawn(5, 5, true));
    EXPECT_FALSE(bishop->canMoveTo(7, 7, &board));
    board.removePiece(5, 5);

    // test movement blocked by other pieces
    board.addPiece(new Pawn(5, 3, true));
    EXPECT_FALSE(bishop->canMoveTo(7, 1, &board));
    board.removePiece(5, 3);
}