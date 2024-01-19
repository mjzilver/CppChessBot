#pragma once

#include "../ChessPiece.h"

class Rook : public ChessPiece {
public:
    Rook(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() { return isWhite ? 'R' : 'r'; }
};