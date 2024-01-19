#pragma once

#include "../ChessPiece.h"

class King : public ChessPiece {
public:
    King(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const { return isWhite ? 'K' : 'k'; }

    bool canMoveTo(int x, int y) {
        if (x == this->x && y == this->y) return false;
        if (abs(x - this->x) > 1 || abs(y - this->y) > 1) return false;
        return true;
    }
};