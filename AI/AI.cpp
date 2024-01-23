#include "AI.h"

#include <chrono>
#include <future>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

void AI::makeMove(ChessBoard* board, bool isWhite) {
    auto start_time = std::chrono::high_resolution_clock::now();
    Move bestMove = findBestMove(board, isWhite);

    std::cout << "Best move: " << board->xyToChessPos(bestMove.fromX, bestMove.fromY);
    std::cout << " to " << board->xyToChessPos(bestMove.toX, bestMove.toY) << std::endl;

    if (!board->movePiece(bestMove.fromX, bestMove.fromY, bestMove.toX, bestMove.toY, isWhite)) {
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
        newBoard->movePiece(move.fromX, move.fromY, move.toX, move.toY, isWhite);
        boardsToDelete.push_back(newBoard);

        futures.push_back(
            std::async(std::launch::async, &AI::minimax, this, newBoard, maxDepth, -10000, 10000, true, !isWhite));
    }

    for (size_t i = 0; i < moves.size(); ++i) {
        // Add some randomness to the score to prevent the AI from always making the same move
        uint randomizer = std::chrono::system_clock::now().time_since_epoch().count();
        float randomScore = (float)rand_r(&randomizer) / RAND_MAX;

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

    // loop over all pieces
    auto pieces = board->getPieces();

    for (auto piece : pieces) {
        if (piece->getIsWhite() == isWhite) {
            // loop over all possible moves
            auto moves = getMovesForPiece(board, piece);

            availableMoves.insert(availableMoves.end(), moves.begin(), moves.end());
        }
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
        newBoard->movePiece(move.fromX, move.fromY, move.toX, move.toY, isWhite);

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

bool AI::isValidMove(ChessBoard* board, ChessPiece* piece, const Move& move) {
    if (piece->canAttack(move.toX, move.toY, board) || piece->canMoveTo(move.toX, move.toY, board)) {
        return true;
    }
    return false;
}

float AI::evaluatePosition(ChessBoard* board, bool isWhite) {
    float whiteScore = 0.0f;
    float blackScore = 0.0f;

    auto pieces = board->getPieces();

    for (auto piece : pieces) {
        float pieceValue = getValueForPiece(piece);

        if (piece->getIsWhite()) {
            whiteScore += pieceValue;
        } else {
            blackScore += pieceValue;
        }

        float centerPoints = calculateCenterPoints(piece->getX(), piece->getY());

        if (piece->getIsWhite()) {
            whiteScore += centerPoints;
        } else {
            blackScore += centerPoints;
        }
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

std::vector<Move> AI::getMovesForPiece(ChessBoard* board, ChessPiece* piece) {
    auto moves = std::vector<Move>();

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            auto move = Move{piece->getX(), piece->getY(), i, j, 0};

            if (isValidMove(board, piece, move)) {
                moves.push_back(move);
            }
        }
    }

    return moves;
}

bool AI::isValidAttack(ChessBoard* board, ChessPiece* piece, const Move& move) {
    return piece->canAttack(move.toX, move.toY, board);
}

float AI::getValueForPiece(ChessPiece* piece) {
    switch (toupper(piece->getSymbol())) {
        case 'P':
            return 10.0f;
        case 'N':
            return 30.0f;
        case 'B':
            return 30.0f;
        case 'R':
            return 50.0f;
        case 'Q':
            return 90.0f;
        case 'K':
            return 900.0f;
        default:
            std::cout << "Error: piece type missing" << std::endl;
            return -0.0f;
    }
}
