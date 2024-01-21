#pragma once

#include "../ChessPiece.h"
#include "../ChessBoard.h"

#include <cmath>

class Knight : public ChessPiece {
public:
    Knight(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const override { return isWhite ? 'N' : 'n'; }

    bool canMoveTo(int toX, int toY, ChessBoard* board) override {
        if (toX == x && toY == y) return false;
        if (abs(toX - x) == 2 && abs(toY - y) == 1) return true;
        if (abs(toX - x) == 1 && abs(toY - y) == 2) return true;
        return false;
    }
};