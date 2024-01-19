#pragma once

#include "../ChessPiece.h"

class Bishop : public ChessPiece {
public:
    Bishop(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const { return isWhite ? 'B' : 'b'; }

    bool canMoveTo(int x, int y) {
        if (x == this->x && y == this->y) return false;
        if (abs(x - this->x) != abs(y - this->y)) return false;
        return true;
    }
};  