#pragma once

#include <vector>

#include "ChessPiece.h"

class ChessBoard {
private:
    char board[8][8];

    std::vector<ChessPiece*> pieces;
public:
    ChessBoard();
    void resetBoard();
    void printBoard();
    void letterToIndex(char letter, int &index);
    ChessPiece* getPiece(int x, int y) const;

    bool movePiece(int fromX, int fromY, int toX, int toY);
};