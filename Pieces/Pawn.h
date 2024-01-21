#pragma once

#include "../ChessPiece.h"
#include "../ChessBoard.h"
#include <cmath>

class Pawn : public ChessPiece {
public:
    Pawn(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const override { return isWhite ? 'P' : 'p'; }

    bool canMoveTo(int toX, int toY, ChessBoard* board) override {
        if (toX == x && toY == y) return false;

        int direction = isWhite ? 1 : -1;
        int distance = hasMoved ? 1 : 2;

        // Move forward
        if (toX == x && abs(toY - y) * direction <= distance) {
            hasMoved = true;
            return true;
        }

        return false;
    }

    bool canAttack(int toX, int toY) override {
        if (toX == x && toY == y) return false;

        int direction = isWhite ? 1 : -1;
        int dx = toX - x;
        int dy = toY - y;

        // Diagonal attack
        if (abs(dx) == 1 && abs(dy) == 1 && y - toY == direction) {
            return true;
        }

        return false;
    }

private:
    bool hasMoved = false;
};
