#pragma once

#include "../ChessPiece.h"
#include "../ChessBoard.h"

#include <cmath>

class Bishop : public ChessPiece {
public:
    Bishop(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const override { return isWhite ? 'B' : 'b'; }

    bool canMoveTo(int toX, int toY, const ChessBoard* board) override {
        if (!ChessPiece::canMoveTo(toX, toY, board)) return false;

        int dx = toX - x;
        int dy = toY - y;

        if (dx == 0 || dy == 0) return false;
        if (abs(dx) != abs(dy)) return false;

        int stepX = dx / abs(dx);
        int stepY = dy / abs(dy);

        for (int i = 1; i < abs(dx); i++) {
            int checkX = x + i * stepX;
            int checkY = y + i * stepY;

            if (board->getPiece(checkX, checkY) != nullptr) return false;
        }

        return true;
    }
};  