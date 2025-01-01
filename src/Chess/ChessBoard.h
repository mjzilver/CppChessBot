#pragma once

#include <cstdint>

#include "PieceType.h"

class ChessBoard {
private:
    bool _gameOver = false;

    uint64_t whitePieces = 0;
    uint64_t blackPieces = 0;
    uint64_t pieces[6] = {0, 0, 0, 0, 0, 0};

    const bool WHITE = true;
    const bool BLACK = false;

    uint64_t zobristTable[12][64];
    uint64_t zobristSideToMove; 
public:
    ChessBoard() {
        resetBoard();
        initializeZobristTable();
    }
    
    // board functions
    void resetBoard();
    void emptyBoard();
    uint64_t getBoard() const { return whitePieces | blackPieces; }
    uint64_t getBoard(const bool isWhite) const { return isWhite ? whitePieces : blackPieces; }

    // Zobrist hashing
    uint64_t getBoardHash(const bool isWhiteMove) const;
    void initializeZobristTable();

    // piece functions
    uint64_t getPieceLocation(const int x, const int y) const { return 1ULL << (x + y * 8); }
    char getPieceSymbol(const int x, const int y) const;
    void setPiece(const int x, const int y, const PieceType pieceType, const bool isWhite);
    void removePiece(const int x, const int y, const PieceType pieceType, const bool isWhite);
    bool isPieceAt(const int x, const int y) const;
    bool isPieceAt(const int x, const int y, const bool isWhite) const;
    bool isPieceAt(const int x, const int y, const PieceType pieceType) const;
    bool isSquareEmpty(const int x, const int y) const { return !isPieceAt(x, y); }
    bool isSquareTaken(const int x, const int y) const { return isPieceAt(x, y); }
    bool getPieceColor(const int x, const int y) const;
    bool removePieceAt(const int x, const int y);
    PieceType getPieceTypeAt(const int x, const int y) const;
    bool movePiece(const int x, const int y, const int newX, const int newY);
    void undoMove(const int x, const int y, const int newX, const int newY, const PieceType capturedPiece);
    uint64_t getValidMoves(const int x, const int y) const;
    uint64_t getValidAttacks(const int x, const int y) const;
    bool isValidMove(const int x, const int y, const int newX, const int newY) const;
    bool isPathClear(const int startX, const int startY, const int endX, const int endY) const;
    bool isValidAttack(const int x, const int y, const int newX, const int newY) const;
};