#include "gtest/gtest.h"
#include "../Pieces/Pawn.h"
#include "../ChessBoard.h"
#include "../ChessPiece.h"

TEST(PawnTest, CanMoveTo) {
    ChessBoard board;
    Pawn* pawn = new Pawn(4, 4, true); 
    board.addPiece(pawn);

    // Test movement in a straight line
    EXPECT_TRUE(pawn->canMoveTo(4, 5, &board));
    EXPECT_TRUE(pawn->canMoveTo(4, 3, &board));

    // Test invalid movement
    EXPECT_FALSE(pawn->canMoveTo(5, 6, &board));
    EXPECT_FALSE(pawn->canMoveTo(3, 6, &board));
    EXPECT_FALSE(pawn->canMoveTo(5, 2, &board));
    EXPECT_FALSE(pawn->canMoveTo(3, 2, &board));
}

TEST(PawnTest, CanMoveToBlocked) {
    ChessBoard board;
    Pawn* pawn = new Pawn(4, 4, true); 
    board.addPiece(pawn);

    // Test movement in a straight line
    board.addPiece(new Pawn(4, 5, true));
    EXPECT_FALSE(pawn->canMoveTo(4, 7, &board));
    board.emptyBoard();
}

TEST(PawnTest, CanAttackDiagonally) {
    ChessBoard board;
    Pawn* pawn = new Pawn(4, 4, false); 
    board.addPiece(pawn);

    // Test movement in a straight line
    board.addPiece(new Pawn(5, 5, true));
    EXPECT_TRUE(pawn->canAttack(5, 5));
    board.emptyBoard();
}