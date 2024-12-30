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

    AI(const AI&) = delete;
    AI& operator=(const AI&) = delete;

    void makeMove(ChessBoard* board, const bool isWhite);

private:
    const int maxDepth;
    const int timeLimit = 2000; 
    uint64_t cacheHitCount = 0;

    // move cache
    std::unordered_map<uint64_t, std::vector<Move>> moveCache;
    std::mutex moveCacheMutex; 

    std::chrono::steady_clock::time_point start_time;

    // evals
    Move findBestMove(const ChessBoard* const board, const bool isWhite);
    float evaluatePosition(const ChessBoard* const board) const;
    int piecePositionScore(const int x, const int y, const PieceType type, const bool isWhite) const;
    float getValueForPiece(const PieceType piece) const;
    float minimax(ChessBoard* const board, const int depth, float alpha, float beta, const bool maximizingPlayer, const bool isWhite);

    // move generation
    std::vector<Move> generateMoves(const ChessBoard* const board, const bool isWhite);
};