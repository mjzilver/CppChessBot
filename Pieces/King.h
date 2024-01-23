#pragma once

#include <cmath>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

class King : public ChessPiece {
public:
    King(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    King(const King& other) : ChessPiece(other) {
        x = other.x;
        y = other.y;
        isWhite = other.isWhite;
    }

    ChessPiece* clone() const override { return new King(*this); }

    char getSymbol() const override { return isWhite ? 'K' : 'k'; }

    bool canMoveTo(int toX, int toY, const ChessBoard* board) override {
        if (!ChessPiece::canMoveTo(toX, toY, board)) return false;

        if (abs(toX - x) > 1 || abs(toY - y) > 1) return false;

        if (board != nullptr) {
            for (auto piece : board->getPieces()) {
                if (piece != nullptr && piece != this && piece->getIsWhite() != isWhite) {
                    if (piece->canAttack(toX, toY, board)) return false;
                }
            }
        }

        return true;
    }
};