#include "AI.h"

#include <atomic>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../Chess/ChessBoard.h"
#include "../Utils/ctz.h"
#include "PieceSqTable.h"

void AI::makeMove(ChessBoard* board, const bool isWhite) {
    start_time = std::chrono::steady_clock::now();
    Move bestMove = findBestMove(board, isWhite);

    if (!board->movePiece(bestMove.fromX, bestMove.fromY, bestMove.toX, bestMove.toY)) {
        std::cout << "AI move failed, this should not happen" << std::endl;
    }
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time to find best move " << duration.count() << " milliseconds\n";
}

Move AI::findBestMove(const ChessBoard* const board, const bool isWhite) {
    float bestScore = -10000.0f;
    Move bestMove{};

    auto moves = generateMoves(board, isWhite);

    std::cout << "Number of moves: " << moves.size() << std::endl;
    std::cout << "Cache hit count: " << cacheHitCount << std::endl;
    cacheHitCount = 0;

    if (moves.empty()) return bestMove;

    std::mutex mutex;
    std::atomic<int> remainingTasks(moves.size());
    std::condition_variable cv;
    std::mutex cv_mutex;

    boost::asio::thread_pool pool(std::thread::hardware_concurrency());

    for (const auto& move : moves) {
        boost::asio::post(pool, [&, move]() {
            ChessBoard* newBoard = new ChessBoard(*board);
            newBoard->movePiece(move.fromX, move.fromY, move.toX, move.toY);
            float score = minimax(newBoard, maxDepth, -10000.0f, 10000.0f, isWhite, !isWhite);
            delete newBoard;

            {
                std::lock_guard<std::mutex> lock(mutex);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }

            if (--remainingTasks == 0) {
                std::lock_guard<std::mutex> lock(cv_mutex);
                cv.notify_one();
            }
        });
    }

    {
        std::unique_lock<std::mutex> lock(cv_mutex);
        cv.wait(lock, [&]() { return remainingTasks == 0; });
    }

    pool.join();

    std::cout << "Best score: " << bestScore << std::endl;

    return bestMove;
}

std::vector<Move> AI::generateMoves(const ChessBoard* const board, const bool isWhite) {
    uint64_t boardHash = board->getBoardHash(isWhite);

    {
        std::lock_guard<std::mutex> lock(moveCacheMutex);
        auto it = moveCache.find(boardHash);
        if (it != moveCache.end()) {
            cacheHitCount++;
            return it->second;
        }
    }

    auto availableMoves = std::vector<Move>();
    uint64_t boardPieces = board->getBoard(isWhite);

    while (boardPieces) {
        int index = ctz(boardPieces);
        int x = index % 8;
        int y = index / 8;

        auto attacks = board->getValidAttacks(x, y);
        auto moves = board->getValidMoves(x, y);

        while (attacks) {
            int attackIndex = ctz(attacks);
            int newX = attackIndex % 8;
            int newY = attackIndex / 8;

            Move move = {x, y, newX, newY, 0};

            availableMoves.push_back(move);

            attacks &= attacks - 1;
        }

        while (moves) {
            int moveIndex = ctz(moves);
            int newX = moveIndex % 8;
            int newY = moveIndex / 8;

            Move move = {x, y, newX, newY, 0};

            availableMoves.push_back(move);

            moves &= moves - 1;
        }

        boardPieces &= boardPieces - 1;
    }

    {
        std::lock_guard<std::mutex> lock(moveCacheMutex);
        moveCache[boardHash] = availableMoves;
    }
    return availableMoves;
}

float AI::minimax(ChessBoard* const board, const int depth, float alpha, float beta, const bool maximizingPlayer,
                  const bool isWhite) {
    if (depth == 0) {
        return evaluatePosition(board);
    }

    // check if time limit has been reached
    auto current_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    if (duration.count() > timeLimit) {
        return evaluatePosition(board);
    }

    float bestScore = maximizingPlayer ? -10000 : 10000;

    auto moves = generateMoves(board, isWhite);

    for (const auto& move : moves) {
        auto piece = board->getPieceTypeAt(move.toX, move.toY);
        board->movePiece(move.fromX, move.fromY, move.toX, move.toY);

        float score = minimax(board, depth - 1, alpha, beta, !maximizingPlayer, !isWhite);

        board->undoMove(move.fromX, move.fromY, move.toX, move.toY, piece);

        if (maximizingPlayer) {
            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, bestScore);
        } else {
            bestScore = std::min(bestScore, score);
            beta = std::min(beta, bestScore);
        }

        if (beta <= alpha) {
            break;  // Prune the search tree
        }
    }

    return bestScore;
}

float AI::evaluatePosition(const ChessBoard* const board) const {
    float whiteScore = 0.0f;
    float blackScore = 0.0f;

    auto evaluatePieces = [&](uint64_t pieces, bool isWhite) {
        float score = 0.0f;
        while (pieces) {
            int index = ctz(pieces);
            int x = index % 8;
            int y = index / 8;

            auto piece = board->getPieceTypeAt(x, y);

            score += getValueForPiece(piece);
            score += piecePositionScore(x, y, piece, isWhite);

            pieces &= pieces - 1;
        }
        return score;
    };

    whiteScore = evaluatePieces(board->getBoard(ChessBoard::WHITE), ChessBoard::WHITE);
    blackScore = evaluatePieces(board->getBoard(ChessBoard::BLACK), ChessBoard::BLACK);

    return blackScore - whiteScore;
}

int AI::piecePositionScore(const int x, const int y, const PieceType type, const bool isWhite) const {
    int i = isWhite ? 0 : 1;
    switch (type) {
        case PAWN:
            return PAWN_TABLE[i][y * 8 + x];
        case KNIGHT:
            return KNIGHT_TABLE[i][y * 8 + x];
        case BISHOP:
            return BISHOP_TABLE[i][y * 8 + x];
        case ROOK:
            return ROOK_TABLE[i][y * 8 + x];
        case QUEEN:
            return QUEEN_TABLE[i][y * 8 + x];
        case KING:
            return KING_TABLE[i][y * 8 + x];
        default:
            return 0;
    }
}

float AI::getValueForPiece(const PieceType piece) const {
    switch (piece) {
        case PAWN:
            return 30.0f;
        case KNIGHT:
            return 70.0f;
        case BISHOP:
            return 70.0f;
        case ROOK:
            return 10.0f;
        case QUEEN:
            return 200.0f;
        case KING:
            return 1000.0f;
        default:
            return 0.0f;
    }
}