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

    ChessBoard(ChessBoard* other) {
        whitePieces = other->whitePieces;
        blackPieces = other->blackPieces;
        pieces[PAWN] = other->pieces[PAWN];
        pieces[ROOK] = other->pieces[ROOK];
        pieces[KNIGHT] = other->pieces[KNIGHT];
        pieces[BISHOP] = other->pieces[BISHOP];
        pieces[QUEEN] = other->pieces[QUEEN];
        pieces[KING] = other->pieces[KING];
    }
    
    // board functions
    void resetBoard();
    void emptyBoard();
    uint64_t getBoard() const {return whitePieces | blackPieces; };
    uint64_t getBoard(bool isWhite) const {return isWhite ? whitePieces : blackPieces; };

    // Zobrist hashing
    uint64_t getBoardHash(bool isWhiteMove) const;
    void initializeZobristTable();

    // piece functions
    uint64_t getPieceLocation(int x, int y) const { return 1ULL << (x + y * 8); }
    char getPieceSymbol(int x, int y) const;
    void setPiece(int x, int y, PieceType pieceType, bool isWhite);
    void removePiece(int x, int y, PieceType pieceType, bool isWhite);
    bool isPieceAt(int x, int y) const;
    bool isPieceAt(int x, int y, bool isWhite) const;
    bool isPieceAt(int x, int y, PieceType pieceType) const;
    bool getPieceColor(int x, int y) const;
    bool removePieceAt(int x, int y);
    PieceType getPieceTypeAt(int x, int y) const;
    bool movePiece(int x, int y, int newX, int newY);
    void undoMove(int x, int y, int newX, int newY, PieceType capturedPiece);
    uint64_t getValidMoves(int x, int y);
    uint64_t getValidAttacks(int x, int y);
    bool isValidMove(int x, int y, int newX, int newY) const;
    bool isPathClear(int startX, int startY, int endX, int endY) const;
    bool isValidAttack(int x, int y, int newX, int newY) const;
};
