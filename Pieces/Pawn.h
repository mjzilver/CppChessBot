#pragma once

#include "../ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() { return isWhite ? 'P' : 'p'; }
};