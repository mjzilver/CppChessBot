#include "gtest/gtest.h"
#include "../Pieces/King.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Queen.h"
#include "../Pieces/Rook.h"
#include "../ChessBoard.h"
#include "../ChessPiece.h"

TEST(KingTest, CanMoveTo) {
    ChessBoard board;
    King* king = new King(4, 4, true);
    board.addPiece(king);

    // Test movement in a straight line
    EXPECT_TRUE(king->canMoveTo(4, 5, &board));
    EXPECT_TRUE(king->canMoveTo(4, 3, &board));
    EXPECT_TRUE(king->canMoveTo(5, 4, &board));
    EXPECT_TRUE(king->canMoveTo(3, 4, &board));

    // Test movement diagonally
    EXPECT_TRUE(king->canMoveTo(5, 5, &board));
    EXPECT_TRUE(king->canMoveTo(3, 3, &board));
    EXPECT_TRUE(king->canMoveTo(5, 3, &board));
    EXPECT_TRUE(king->canMoveTo(3, 5, &board));

    // Test invalid movement
    EXPECT_FALSE(king->canMoveTo(5, 6, &board));
    EXPECT_FALSE(king->canMoveTo(3, 6, &board));
    EXPECT_FALSE(king->canMoveTo(5, 2, &board));
}

TEST(KingTest, CanMoveToBlocking) {
    ChessBoard board;
    King* king = new King(4, 4, true);
    board.addPiece(king);

    // Test movement in a straight line
    board.addPiece(new Pawn(4, 5, true));
    EXPECT_FALSE(king->canMoveTo(4, 7, &board));
    board.removePiece(4, 5);

    // Test movement diagonally
    board.addPiece(new Pawn(5, 5, true));
    EXPECT_FALSE(king->canMoveTo(7, 7, &board));
    board.removePiece(5, 5);

    // test movement blocked by other pieces
    board.addPiece(new Pawn(5, 3, true));
    EXPECT_FALSE(king->canMoveTo(7, 1, &board));
    board.removePiece(5, 3);
}

TEST(KingTest, CantMoveToEnemyLineOfSight)
{
    ChessBoard board;
    King* king = new King(4, 4, true);
    board.addPiece(king);

    board.addPiece(new Rook(8, 5, false));
    EXPECT_FALSE(king->canMoveTo(4, 5, &board));
    board.removePiece(8, 5);

    board.addPiece(new Rook(8, 3, false));
    EXPECT_FALSE(king->canMoveTo(4, 3, &board));
    board.removePiece(8, 3);

    board.addPiece(new Rook(5, 8, false));
    EXPECT_FALSE(king->canMoveTo(5, 4, &board));
    board.removePiece(5, 8);

    board.addPiece(new Rook(3, 8, false));
    EXPECT_FALSE(king->canMoveTo(3, 4, &board));
    board.removePiece(3, 8);
}