#pragma once

#include <cstdint>

#include "PieceType.h"

class ChessBoard {
private:
    bool _gameOver = false;

    uint64_t whitePieces = 0;
    uint64_t blackPieces = 0;
    uint64_t pieces[6] = {0, 0, 0, 0, 0, 0};

public:
    // board functions
    void resetBoard();
    void emptyBoard();
    uint64_t getBoard() const {return whitePieces | blackPieces; };
    uint64_t getBoard(bool isWhite) const {return isWhite ? whitePieces : blackPieces; };

    // piece functions
    uint64_t getPieceLocation(int x, int y) const;
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
    uint64_t getAllValidMovesForPiece(int x, int y);
    bool isValidMove(int x, int y, int newX, int newY) const;
    bool isPathClear(int startX, int startY, int endX, int endY) const;
    bool isValidAttack(int x, int y, int newX, int newY) const;
};
