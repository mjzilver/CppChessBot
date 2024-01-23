#pragma once

#include "../ChessBoard.h"
#include "../ChessPiece.h"

class Rook : public ChessPiece {
public:
    Rook(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite, 5) {}

    char getSymbol() const override { return isWhite ? 'R' : 'r'; }

    bool canMoveTo(int toX, int toY, const ChessBoard* board) override {
        if (!ChessPiece::canMoveTo(toX, toY, board)) return false;
        if (toX != x && toY != y) return false;

        int dx = toX - x;
        int dy = toY - y;

        // steps to check for pieces in the way
        // 0 if no movement in that direction
        int stepX = dx == 0 ? 0 : dx / abs(dx);
        int stepY = dy == 0 ? 0 : dy / abs(dy);

        for (int i = 1; i < std::max(abs(dx), abs(dy)); i++) {
            int checkX = x + i * stepX;
            int checkY = y + i * stepY;

            if (board->getPiece(checkX, checkY) != nullptr) return false;
        }

        return true;
    }
};