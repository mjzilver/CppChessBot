#pragma once

#include "../ChessPiece.h"

class Queen : public ChessPiece {
public:
    Queen(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const { return isWhite ? 'Q' : 'q'; }

    bool canMoveTo(int x, int y) {
        if (x == this->x && y == this->y) return false;
        if (abs(x - this->x) == abs(y - this->y)) return true;
        if (x == this->x || y == this->y) return true;
        return false;
    }
};