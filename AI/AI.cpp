#include "AI.h"

#include <iostream>
#include <limits>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

// Define constants for evaluation
const float CHECKMATE_SCORE = 1000.0f;
const float DRAW_SCORE = 0.0f;

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

    auto moves = generateMoves(board, isWhite);

    for (const auto& move : moves) {
        ChessBoard* newBoard = new ChessBoard(*board);
        newBoard->movePiece(move.fromX, move.fromY, move.toX, move.toY, isWhite);

        float score = minimax(newBoard, 2, -10000, 10000, true, !isWhite);

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
        float pieceValue = getValueForPiece(piece);

        if (piece->getIsWhite()) {
            whiteScore += pieceValue;
        } else {
            blackScore += pieceValue;
        }
    }

    return isWhite ? (whiteScore - blackScore) : (blackScore - whiteScore);
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
    // Assign values to each piece
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
            std::cout << "!!!!!!! Unknown piece type" << std::endl;
            return 12.4f;  // Unknown piece type
    }
}
