#include "AI.h"

#include <chrono>
#include <future>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>
#include <cstdlib>
#include <random>

#include "../ChessBoard.h"

void AI::makeMove(ChessBoard* board, bool isWhite) {
    auto start_time = std::chrono::high_resolution_clock::now();
    Move bestMove = findBestMove(board, isWhite);

    if (!board->movePiece(bestMove.fromX, bestMove.fromY, bestMove.toX, bestMove.toY)) {
        std::cout << "AI move failed, this should not happen" << std::endl;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time to find best move " << duration.count() << " milliseconds\n";
}

Move AI::findBestMove(ChessBoard* board, bool isWhite) {
    float bestScore = -10000;
    Move bestMove;

    auto moves = generateMoves(board, isWhite);

    std::vector<std::future<float>> futures;
    std::vector<ChessBoard*> boardsToDelete;

    for (const auto& move : moves) {
        ChessBoard* newBoard = new ChessBoard(*board);
        newBoard->movePiece(move.fromX, move.fromY, move.toX, move.toY);
        boardsToDelete.push_back(newBoard);

        futures.push_back(
            std::async(std::launch::async, &AI::minimax, this, newBoard, maxDepth, -10000, 10000, true, !isWhite));
    }

    for (size_t i = 0; i < moves.size(); ++i) {
        // Add some randomness to the score to prevent the AI from always making the same move
        int randomizer = std::chrono::system_clock::now().time_since_epoch().count();
        float randomScore = (float)std::rand() / (float)RAND_MAX;

        float score = futures[i].get() + randomScore;

        if (score > bestScore) {
            bestScore = score;
            bestMove = moves[i];
        }
    }

    for (auto board : boardsToDelete) {
        delete board;
    }

    std::cout << "Best score: " << bestScore << std::endl;

    return bestMove;
}

std::vector<Move> AI::generateMoves(ChessBoard* board, bool isWhite) {
    auto availableMoves = std::vector<Move>();

    // Get all pieces for the current player and generate moves for each piece
    uint64_t boardPieces = board->getBoard(isWhite);

    // Loop through all pieces in the bitboard
    while (boardPieces) {
        int index = __builtin_ctzll(boardPieces);
        int x = index % 8;
        int y = index / 8;

        auto piece = board->getPieceTypeAt(x, y);

        auto moves = board->getAllValidMovesForPiece(x, y);

        // Loop through all moves in the bitboard
        while (moves) {
            int moveIndex = __builtin_ctzll(moves);
            int newX = moveIndex % 8;
            int newY = moveIndex / 8;

            Move move = {x, y, newX, newY, 0.0f};

            availableMoves.push_back(move);

            moves &= moves - 1;
        }

        boardPieces &= boardPieces - 1;
    }

    return availableMoves;
}

float AI::minimax(ChessBoard* board, int depth, float alpha, float beta, bool maximizingPlayer, bool isWhite) {
    if (depth == 0) {
        return evaluatePosition(board, isWhite);
    }
    float bestScore = maximizingPlayer ? -10000 : 10000;

    auto moves = generateMoves(board, isWhite);

    for (const auto& move : moves) {
        ChessBoard* newBoard = new ChessBoard(*board);
        newBoard->movePiece(move.fromX, move.fromY, move.toX, move.toY);

        float score = minimax(newBoard, depth - 1, alpha, beta, !maximizingPlayer, !isWhite);

        if (maximizingPlayer) {
            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, bestScore);
        } else {
            bestScore = std::min(bestScore, score);
            beta = std::min(beta, bestScore);
        }

        delete newBoard;

        if (beta <= alpha) {
            break;  // Prune the search tree
        }
    }

    return bestScore;
}

float AI::evaluatePosition(ChessBoard* board, bool isWhite) {
    float whiteScore = 0.0f;
    float blackScore = 0.0f;

    auto whitePieces = board->getBoard(true);
    auto blackPieces = board->getBoard(false);

    // Loop through all pieces in the bitboard
    while (whitePieces) {
        int index = __builtin_ctzll(whitePieces);
        int x = index % 8;
        int y = index / 8;

        auto piece = board->getPieceTypeAt(x, y);

        whiteScore += getValueForPiece(piece);
        whiteScore += calculateCenterPoints(x, y);

        whitePieces &= whitePieces - 1;
    }

    // Loop through all pieces in the bitboard
    while (blackPieces) {
        int index = __builtin_ctzll(blackPieces);
        int x = index % 8;
        int y = index / 8;

        auto piece = board->getPieceTypeAt(x, y);

        blackScore += getValueForPiece(piece);
        blackScore += calculateCenterPoints(x, y);

        blackPieces &= blackPieces - 1;
    }

    return isWhite ? (whiteScore - blackScore) : (blackScore - whiteScore);
}

float AI::calculateCenterPoints(int x, int y) {
    float centerX = 3.5f;
    float centerY = 3.5f;

    float distanceX = std::min(x, 7 - x);
    float distanceY = std::min(y, 7 - y);

    float maxDistance = std::max(centerX, centerY);

    float centerPoints = 1.0f - (std::min(distanceX, distanceY) / maxDistance);
    centerPoints = std::max(centerPoints, 0.0f);  // Ensure points are not negative

    return centerPoints;
}


float AI::getValueForPiece(PieceType piece) {
    switch (piece) {
        case PAWN:
            return 10.0f;
        case KNIGHT:
            return 30.0f;
        case BISHOP:
            return 30.0f;
        case ROOK:
            return 50.0f;
        case QUEEN:
            return 90.0f;
        case KING:
            return 1000.0f;
        default:
            return 0.0f;
    }
}
