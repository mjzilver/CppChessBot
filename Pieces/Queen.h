#pragma once

#include "../ChessPiece.h"
#include "../ChessBoard.h"

class Queen : public ChessPiece
{
public:
    Queen(int x, int y, bool isWhite) : ChessPiece(x, y, isWhite) {}

    char getSymbol() const override { return isWhite ? 'Q' : 'q'; }

    bool canMoveTo(int toX, int toY, ChessBoard *board) override
    {
        int dx = toX - x;
        int dy = toY - y;

        // Check if the move is either in a straight line or diagonal
        if (dx == 0 || dy == 0 || abs(dx) == abs(dy))
        {
            // Calculate the direction of the move
            int stepX = (dx == 0) ? 0 : dx / abs(dx);
            int stepY = (dy == 0) ? 0 : dy / abs(dy);

            // Check each square along the path for a piece
            for (int i = 1; i < std::max(abs(dx), abs(dy)); i++)
            {
                int checkX = x + i * stepX;
                int checkY = y + i * stepY;

                if (board->getPiece(checkX, checkY) != nullptr)
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }
};