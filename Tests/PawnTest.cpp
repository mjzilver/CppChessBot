#include "gtest/gtest.h"
#include "../Pieces/Pawn.h"
#include "../ChessBoard.h"
#include "../ChessPiece.h"

TEST(PawnTest, CanMoveTo) {
    ChessBoard board;
    Pawn* pawn = new Pawn(4, 4, true); 
    board.addPiece(pawn);

    // white can only move into negative y direction
    // Test movement in a straight line
    EXPECT_TRUE(pawn->canMoveTo(4, 3, &board));

    // pawn cannot move backwards
    EXPECT_FALSE(pawn->canMoveTo(4, 5, &board));

    // Test invalid movement
    EXPECT_FALSE(pawn->canMoveTo(5, 6, &board));
    EXPECT_FALSE(pawn->canMoveTo(3, 6, &board));
    EXPECT_FALSE(pawn->canMoveTo(5, 2, &board));
    EXPECT_FALSE(pawn->canMoveTo(3, 2, &board));
}

TEST(PawnTest, CanMoveTwoSquares) {
    ChessBoard board;
    Pawn* pawn = new Pawn(4, 4, true); 
    board.addPiece(pawn);

    // white can only move into negative y direction
    EXPECT_TRUE(pawn->canMoveTo(4, 2, &board));

    board.emptyBoard();
    board.addPiece(new Pawn(2, 2, false));

    // black can only move into positive y direction
    EXPECT_TRUE(pawn->canMoveTo(2, 4, &board));
}

TEST(PawnTest, CanMoveToBlocked) {
    ChessBoard board;
    Pawn* pawn = new Pawn(4, 4, true); 
    board.addPiece(pawn);

    board.addPiece(new Pawn(4, 5, true));
    EXPECT_FALSE(pawn->canMoveTo(4, 7, &board));
    board.emptyBoard();
}

TEST(PawnTest, CanAttackDiagonally) {
    ChessBoard board;
    Pawn* pawn = new Pawn(4, 4, true); 
    board.addPiece(pawn);

        // Test white pawn attacking diagonally
    EXPECT_TRUE(pawn->canAttack(5, 3, &board));
    EXPECT_TRUE(pawn->canAttack(3, 3, &board));

    // Test black pawn attacking diagonally
    pawn = new Pawn(4, 4, false);
    board.addPiece(pawn);
    EXPECT_TRUE(pawn->canAttack(5, 5, &board));
    EXPECT_TRUE(pawn->canAttack(3, 5, &board));

    // Ensure pawns cannot attack vertically or horizontally
    EXPECT_FALSE(pawn->canAttack(4, 3, &board));
    EXPECT_FALSE(pawn->canAttack(4, 5, &board));
    EXPECT_FALSE(pawn->canAttack(5, 4, &board));
    EXPECT_FALSE(pawn->canAttack(3, 4, &board));
}

TEST(PawnTest, PawnPromotion) {
    ChessBoard board;

    // white pawn promotion
    Pawn* pawn = new Pawn(0, 1, true);
    board.addPiece(pawn);
    EXPECT_TRUE(board.movePiece(0, 1, 0, 0, true, 'Q'));
    EXPECT_EQ(board.getPiece(0, 1), nullptr);
    EXPECT_EQ(board.getPiece(0, 0)->getSymbol(), 'Q');

    // black pawn promotion
    Pawn* pawn2 = new Pawn(0, 6, false);
    board.addPiece(pawn2);
    EXPECT_TRUE(board.movePiece(0, 6, 0, 7, false, 'q'));
    EXPECT_EQ(board.getPiece(0, 6), nullptr);
    EXPECT_EQ(board.getPiece(0, 7)->getSymbol(), 'q');

    // promote to knight
    board.emptyBoard();
    board.addPiece(new Pawn(0, 1, true));
    EXPECT_TRUE(board.movePiece(0, 1, 0, 0, true, 'N'));
    EXPECT_EQ(board.getPiece(0, 1), nullptr);
    EXPECT_EQ(board.getPiece(0, 0)->getSymbol(), 'N');

    // promote to bishop
    board.emptyBoard();
    board.addPiece(new Pawn(0, 1, true));
    EXPECT_TRUE(board.movePiece(0, 1, 0, 0, true, 'B'));
    EXPECT_EQ(board.getPiece(0, 1), nullptr);
    EXPECT_EQ(board.getPiece(0, 0)->getSymbol(), 'B');

    // invalid promotion
    board.emptyBoard();
    board.addPiece(new Pawn(0, 1, true));
    EXPECT_FALSE(board.movePiece(0, 1, 0, 0, true, 'K'));
    EXPECT_EQ(board.getPiece(0, 1)->getSymbol(), 'P');
    EXPECT_EQ(board.getPiece(0, 0), nullptr);

    // if you dont specify a piece to promote to, it defaults to queen
    board.emptyBoard();
    board.addPiece(new Pawn(0, 1, true));
    EXPECT_TRUE(board.movePiece(0, 1, 0, 0, true));
    EXPECT_EQ(board.getPiece(0, 1), nullptr);
    EXPECT_EQ(board.getPiece(0, 0)->getSymbol(), 'Q');
}