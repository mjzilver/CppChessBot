// AI.h

#ifndef AI_H
#define AI_H

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

    Move findBestMove(ChessBoard* board, bool isWhite);
    float evaluatePosition(ChessBoard* board, bool isWhite);
    float minimax(ChessBoard* board, int depth, float alpha, float beta, bool maximizingPlayer, bool isWhite);

    std::vector<Move> getMovesForPiece(ChessBoard* board, ChessPiece* piece, bool considerAttacks = false);
    float getValueForPiece(ChessPiece* piece);

    std::vector<Move> generateMoves(ChessBoard* board, bool isWhite);
    bool isValidMove(ChessBoard* board, ChessPiece* piece, const Move& move);
    bool isValidAttack(ChessBoard* board, ChessPiece* piece, const Move& move);
};

#endif  // AI_H
