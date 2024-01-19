#pragma once

#include "../ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const { return isWhite ? 'N' : 'n'; }

    bool canMoveTo(int x, int y) {
        if (x == this->x && y == this->y) return false;
        if (abs(x - this->x) == 2 && abs(y - this->y) == 1) return true;
        if (abs(x - this->x) == 1 && abs(y - this->y) == 2) return true;
        return false;
    }
};