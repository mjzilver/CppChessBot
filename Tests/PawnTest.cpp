#include "gtest/gtest.h"
#include "../Pieces/Pawn.h"
#include "../ChessBoard.h"
#include "../ChessPiece.h"
#include "../Player.h"

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

    board.addPiece(new Pawn(5, 5, false));
    EXPECT_TRUE(pawn->canAttack(5, 5));
    board.emptyBoard();
}

TEST(PawnTest, PawnPromotion) {
    ChessBoard board;

    // white pawn promotion
    Player* player = new Player(true);
    Pawn* pawn = new Pawn(0, 1, true);
    board.addPiece(pawn);
    EXPECT_TRUE(player->makeMove(board, "a7a8Q"));
    EXPECT_EQ(board.getPiece(0, 1), nullptr);
    EXPECT_EQ(board.getPiece(0, 0)->getSymbol(), 'Q');

    // black pawn promotion
    Player* player2 = new Player(false);
    Pawn* pawn2 = new Pawn(0, 6, false);
    board.addPiece(pawn2);
    EXPECT_TRUE(player2->makeMove(board, "a2a1Q"));
    EXPECT_EQ(board.getPiece(0, 6), nullptr);
    EXPECT_EQ(board.getPiece(0, 7)->getSymbol(), 'q');

    // invalid promotion
    board.emptyBoard();
    board.addPiece(new Pawn(0, 1, true));
    EXPECT_FALSE(player->makeMove(board, "a7a8X"));
    EXPECT_EQ(board.getPiece(0, 1)->getSymbol(), 'P');
    EXPECT_EQ(board.getPiece(0, 0), nullptr);

    // invalid promotion
    board.emptyBoard();
    board.addPiece(new Pawn(0, 1, true));
    EXPECT_FALSE(player->makeMove(board, "a7a8"));
    EXPECT_EQ(board.getPiece(0, 1)->getSymbol(), 'P');
    EXPECT_EQ(board.getPiece(0, 0), nullptr);
}