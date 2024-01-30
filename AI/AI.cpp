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
#include "PieceSqTable.h"

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
            std::async(std::launch::async, &AI::minimax, this, newBoard, maxDepth, -10000, 10000, false, !isWhite));
    }

    for (size_t i = 0; i < moves.size(); ++i) {
        float score = futures[i].get();

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

        auto attacks = board->getValidAttacks(x, y);
        auto moves = board->getValidMoves(x, y);

        // Loop through all attacks in the bitboard
        while (attacks) {
            int attackIndex = __builtin_ctzll(attacks);
            int newX = attackIndex % 8;
            int newY = attackIndex / 8;

            int score = getValueForPiece(board->getPieceTypeAt(newX, newY));

            Move move = {x, y, newX, newY, score};

            availableMoves.push_back(move);

            attacks &= attacks - 1;
        }

        // Loop through all moves in the bitboard
        while (moves) {
            int moveIndex = __builtin_ctzll(moves);
            int newX = moveIndex % 8;
            int newY = moveIndex / 8;

            int score = piecePositionScore(newX, newY, piece, isWhite);            

            Move move = {x, y, newX, newY, score};

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
        whiteScore += piecePositionScore(x, y, piece, true);

        whitePieces &= whitePieces - 1;
    }

    // Loop through all pieces in the bitboard
    while (blackPieces) {
        int index = __builtin_ctzll(blackPieces);
        int x = index % 8;
        int y = index / 8;

        auto piece = board->getPieceTypeAt(x, y);

        blackScore += getValueForPiece(piece);
        blackScore += piecePositionScore(x, y, piece, false);

        blackPieces &= blackPieces - 1;
    }

    return isWhite ? (whiteScore - blackScore) : (blackScore - whiteScore);
}

int AI::piecePositionScore(int x, int y, char symbol, bool isWhite) {
    switch (toupper(symbol)) {
        case 'P':
            return PAWN_TABLE[isWhite ? 0 : 1][y * 8 + x];
        case 'N':
            return KNIGHT_TABLE[isWhite ? 0 : 1][y * 8 + x];
        case 'B':
            return BISHOP_TABLE[isWhite ? 0 : 1][y * 8 + x];
        case 'R':
            return ROOK_TABLE[isWhite ? 0 : 1][y * 8 + x];
        case 'Q':
            return QUEEN_TABLE[isWhite ? 0 : 1][y * 8 + x];
        case 'K':
            return KING_TABLE[isWhite ? 0 : 1][y * 8 + x];
        default:
            return 0;
    }
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