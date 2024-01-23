#pragma once

#include <cmath>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite, 3) {}

    char getSymbol() const override { return isWhite ? 'N' : 'n'; }

    bool canMoveTo(int toX, int toY, const ChessBoard* const board) override {
        if (!ChessPiece::canMoveTo(toX, toY, board)) return false;
        if (abs(toX - x) == 2 && abs(toY - y) == 1) return true;
        if (abs(toX - x) == 1 && abs(toY - y) == 2) return true;
        return false;
    }
};