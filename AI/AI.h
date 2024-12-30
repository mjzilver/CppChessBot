#pragma once

#include "../ChessBoard.h"
#include "../PieceType.h"

#include <vector>
#include <unordered_map>
#include <mutex>

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
    const int timeLimit = 5000; // 5 seconds TODO implement time limit

    // move cache
    std::unordered_map<uint64_t, std::vector<Move>> moveCache;
    std::mutex moveCacheMutex; 

    // evals
    Move findBestMove(ChessBoard* board, bool isWhite);
    float evaluatePosition(ChessBoard* board);
    int piecePositionScore(int x, int y, PieceType type, bool isWhite);
    float getValueForPiece(PieceType piece);
    float minimax(ChessBoard* board, int depth, float alpha, float beta, bool maximizingPlayer, bool isWhite);

    // move generation
    std::vector<Move> generateMoves(ChessBoard* board, bool isWhite);
};
