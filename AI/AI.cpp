#include "AI.h"

#include <iostream>
#include <limits>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

// Define constants for evaluation
const float CHECKMATE_SCORE = 1000.0f;
const float DRAW_SCORE = 0.0f;

float AI::minimax(ChessBoard* board, int depth, float alpha, float beta, bool maximizingPlayer, bool isWhite) {
    if (depth < 1 || board->isGameOver()) {
        return evaluatePosition(board, isWhite);
    }
    std::cout << "depth: " << depth << std::endl;

    float bestScore = maximizingPlayer ? -1000 : 1000;

    auto moves = generateMoves(board, isWhite);

    std::cout << "checking moves..." << moves.size() << std::endl;
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

bool AI::isValidMove(ChessBoard* board, ChessPiece* piece, const Move& move) {
    if (piece->canAttack(move.toX, move.toY, board) || piece->canMoveTo(move.toX, move.toY, board)) {
        return true;
    }
    return false;
}

Move AI::findBestMove(ChessBoard* board, bool isWhite) {
    float bestScore = -1000;
    Move bestMove;

    std::cout << "Generating moves..." << std::endl;
    auto moves = generateMoves(board, isWhite);

    std::cout << "Evaluating moves..." << std::endl;
    for (const auto& move : moves) {
        std::cout << "Copying board..." << std::endl;
        ChessBoard* newBoard = new ChessBoard(*board);
        std::cout << "Moving piece..." << std::endl;
        newBoard->movePiece(move.fromX, move.fromY, move.toX, move.toY, isWhite);
        std::cout << "Move completed..." << std::endl;

        std::cout << "Evaluating move: " << std::endl;
        float score = minimax(newBoard, 2, -1000, 1000, false, !isWhite);
        std::cout << "Score: " << score << std::endl;
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }

        delete newBoard;
    }

    std::cout << "Best score: " << bestScore << std::endl;
    return bestMove;
}

void AI::makeMove(ChessBoard* board, bool isWhite) {
    std::cout << "AI is thinking..." << std::endl;
    Move bestMove = findBestMove(board, isWhite);

    std::cout << "AI move: " << board->xyToChessPos(bestMove.fromX, bestMove.fromY);
    std::cout << " -> " << board->xyToChessPos(bestMove.toX, bestMove.toY);
    std::cout << " (" << bestMove.score << ")" << std::endl;

    if (!board->movePiece(bestMove.fromX, bestMove.fromY, bestMove.toX, bestMove.toY, isWhite)) {
        std::cout << "AI move failed" << std::endl;
    }
}

float AI::evaluatePosition(ChessBoard* board, bool isWhite) {
    float whiteScore = 0.0f;
    float blackScore = 0.0f;

    auto pieces = board->getPieces();

    for (auto piece : pieces) {
        if (piece->getIsWhite()) {
            whiteScore += getValueForPiece(piece);
        } else {
            blackScore += getValueForPiece(piece);
        }
    }

    return isWhite ? (whiteScore - blackScore) : (blackScore - whiteScore);
}

float AI::getValueForPiece(ChessPiece* piece) {
    // Assign values to each piece
    switch (toupper(piece->getSymbol())) {
        case 'P':
            return 1.0f;
        case 'N':
            return 3.0f;
        case 'B':
            return 3.0f;
        case 'R':
            return 5.0f;
        case 'Q':
            return 9.0f;
        case 'K':
            return 100.0f;
        default:
            return 0.0f;  // Unknown piece type
    }
}
