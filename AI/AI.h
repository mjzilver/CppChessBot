#pragma once

#include "../ChessBoard.h"

struct Move {
    int fromX, fromY;
    int toX, toY;
    float score;  // Add any additional information you may need for a move
};

class AI {
public:
    AI(int maxDepth) : maxDepth(maxDepth) {}

    void makeMove(ChessBoard* board, bool isWhite);

private:
    int maxDepth;

    // evals
    Move findBestMove(ChessBoard* board, bool isWhite);
    float evaluatePosition(ChessBoard* board, bool isWhite);
    float calculateCenterPoints(int x, int y);
    float minimax(ChessBoard* board, int depth, float alpha, float beta, bool maximizingPlayer, bool isWhite);

    // helper functions
    std::vector<Move> getMovesForPiece(ChessBoard* board, ChessPiece* piece);
    float getValueForPiece(ChessPiece* piece);

    // move generation
    std::vector<Move> generateMoves(ChessBoard* board, bool isWhite);
    bool isValidMove(ChessBoard* board, ChessPiece* piece, const Move& move);
    bool isValidAttack(ChessBoard* board, ChessPiece* piece, const Move& move);
};
