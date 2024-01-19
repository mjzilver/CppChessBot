#pragma once

#include "../ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() { return isWhite ? 'N' : 'n'; }
};