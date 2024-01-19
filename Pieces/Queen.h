#pragma once

#include "../ChessPiece.h"

class Queen : public ChessPiece {
public:
    Queen(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() { return isWhite ? 'Q' : 'q'; }
};