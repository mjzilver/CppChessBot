#pragma once

#include "../ChessPiece.h"

class King : public ChessPiece {
public:
    King(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() { return isWhite ? 'K' : 'k'; }
};