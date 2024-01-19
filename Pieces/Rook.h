#pragma once

#include "../ChessPiece.h"

class Rook : public ChessPiece {
public:
    Rook(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const { return isWhite ? 'R' : 'r'; }

    bool canMoveTo(int x, int y) {
        if (x == this->x && y == this->y) return false;
        if (x != this->x && y != this->y) return false;
        return true;
    }
};