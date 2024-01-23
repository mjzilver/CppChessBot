#pragma once

#include <cmath>
#include <iostream>

#include "../ChessBoard.h"
#include "../ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    Pawn(const Pawn& other) : ChessPiece(other) {
        x = other.x;
        y = other.y;
        isWhite = other.isWhite;
    }

    ChessPiece* clone() const override { return new Pawn(*this); }

    char getSymbol() const override { return isWhite ? 'P' : 'p'; }

    void moveTo(int toX, int toY) override {
        hasMoved = true;
        ChessPiece::moveTo(toX, toY);
    }

    bool canMoveTo(int toX, int toY, const ChessBoard* board) override {
        if (!ChessPiece::canMoveTo(toX, toY, board)) return false;
        // Check if blocked (cant move or attack forward)
        if (board->getPiece(toX, toY) != nullptr) return false;
        int direction = isWhite ? -1 : 1;

        // Move forward 1
        if (toX == x && toY == y + direction) {
            return true;
        }
        // move forward 2
        if (toX == x && toY == y + direction * 2 && !hasMoved) {
            // check if not blocked
            if (board->getPiece(toX, toY - direction) != nullptr) {
                return false;
            }
            return true;
        }

        return false;
    }

    bool canAttack(int toX, int toY, const ChessBoard* board) override {
        int direction = isWhite ? -1 : 1;
        int dx = toX - x;
        int dy = toY - y;

        // Diagonal attack
        if (abs(dx) == 1 && abs(dy) == 1 && y - toY == -direction) {
            // Check if there is a piece to attack
            if (board->getPiece(toX, toY) == nullptr) {
                return false;
            }
            // Check if the piece is an enemy
            if (board->getPiece(toX, toY)->getIsWhite() == isWhite) {
                return false;
            }

            return true;
        }

        return false;
    }

private:
    bool hasMoved = false;
};
