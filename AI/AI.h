#pragma once

#include "../ChessBoard.h"
#include "../PieceType.h"

#include <vector>

struct Move {
    int fromX, fromY;
    int toX, toY;
    float score; 
};

class AI {
public:
    AI(int maxDepth) : maxDepth(maxDepth) {}

    void makeMove(ChessBoard* board, bool isWhite);

private:
    int maxDepth;

    // evals
    Move findBestMove(ChessBoard* board, bool isWhite);
    float evaluatePosition(ChessBoard* board);
    int piecePositionScore(int x, int y, PieceType type, bool isWhite);
    float getValueForPiece(PieceType piece);
    float minimax(ChessBoard* board, int depth, float alpha, float beta, bool maximizingPlayer, bool isWhite);

    // move generation
    std::vector<Move> generateMoves(ChessBoard* board, bool isWhite);
};
