#include "../ChessBoard.h"
#include "../ChessPiece.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Queen.h"
#include "gtest/gtest.h"

TEST(QueenTest, CanMoveTo) {
    ChessBoard board;
    Queen* queen = new Queen(4, 4, true);
    board.addPiece(queen);

    // Test movement in a straight line
    EXPECT_TRUE(queen->canMoveTo(4, 7, &board));
    EXPECT_TRUE(queen->canMoveTo(4, 1, &board));
    EXPECT_TRUE(queen->canMoveTo(7, 4, &board));
    EXPECT_TRUE(queen->canMoveTo(1, 4, &board));

    // Test movement diagonally
    EXPECT_TRUE(queen->canMoveTo(7, 7, &board));
    EXPECT_TRUE(queen->canMoveTo(1, 1, &board));
    EXPECT_TRUE(queen->canMoveTo(7, 1, &board));
    EXPECT_TRUE(queen->canMoveTo(1, 7, &board));

    // Test invalid movement
    EXPECT_FALSE(queen->canMoveTo(5, 6, &board));
    EXPECT_FALSE(queen->canMoveTo(3, 6, &board));
    EXPECT_FALSE(queen->canMoveTo(5, 2, &board));
    EXPECT_FALSE(queen->canMoveTo(3, 2, &board));
}

TEST(QueenTest, CanMoveToBlocked) {
    ChessBoard board;
    Queen* queen = new Queen(4, 4, true);
    board.addPiece(queen);

    // Test movement in a straight line
    board.addPiece(new Pawn(4, 5, true));
    EXPECT_FALSE(queen->canMoveTo(4, 7, &board));
    board.removePiece(4, 5);

    // Test movement diagonally
    board.addPiece(new Pawn(5, 5, true));
    EXPECT_FALSE(queen->canMoveTo(7, 7, &board));
    board.removePiece(5, 5);

    // test movement blocked by other pieces
    board.addPiece(new Pawn(5, 3, true));
    EXPECT_FALSE(queen->canMoveTo(7, 1, &board));
    board.removePiece(5, 3);
}