#pragma once

#include <cmath>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    Knight(const Knight& other) : ChessPiece(other) {
        x = other.x;
        y = other.y;
        isWhite = other.isWhite;
    }

    ChessPiece* clone() const override { return new Knight(*this); }

    char getSymbol() const override { return isWhite ? 'N' : 'n'; }

    bool canMoveTo(int toX, int toY, const ChessBoard* board) override {
        if (!ChessPiece::canMoveTo(toX, toY, board)) return false;
        if (abs(toX - x) == 2 && abs(toY - y) == 1) return true;
        if (abs(toX - x) == 1 && abs(toY - y) == 2) return true;
        return false;
    }
};