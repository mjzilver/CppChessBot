#pragma once

#include "../ChessPiece.h"
#include <cmath>

class Pawn : public ChessPiece {
public:
    Pawn(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const { return isWhite ? 'P' : 'p'; }

    bool canMoveTo(int newX, int newY) {
        if (newX == x && newY == y) return false;

        int direction = isWhite ? 1 : -1;
        int distance = hasMoved ? 1 : 2;

        // Move forward
        if (newX == x && std::abs(newY -y) * direction <= distance) {
            hasMoved = true;
            return true;
        }

        return false;
    }

    bool canAttack(int newX, int newY) override {
        if (newX == x && newY == y) return false;

        int direction = isWhite ? 1 : -1;

        // Diagonal attack
        if (std::abs(newX - x) == 1 && std::abs(newY - y) == 1 && y - newY == direction) {
            return true;
        }

        return false;
    }

private:
    bool hasMoved = false;
};
