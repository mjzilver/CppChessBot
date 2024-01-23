#pragma once

#include <cmath>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

class King : public ChessPiece {
public:
    King(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite, 20) {}

    char getSymbol() const override { return isWhite ? 'K' : 'k'; }

    bool canMoveTo(int toX, int toY, const ChessBoard* const board) override {
        if (!ChessPiece::canMoveTo(toX, toY, board)) return false;

        if (abs(toX - x) > 1 || abs(toY - y) > 1) return false;

        for (int i = 0; i < board->getPieces().size(); i++) {
            if (board->getPieces()[i]->getIsWhite() != isWhite) {
                if (board->getPieces()[i]->canAttack(toX, toY, board)) return false;
            }
        }

        return true;
    }
};