#pragma once

#include "../ChessPiece.h"

class Bishop : public ChessPiece {
public:
    Bishop(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() { return isWhite ? 'B' : 'b'; }
};  