#pragma once

#include <vector>

#include "ChessPiece.h"

#include <string>

class ChessBoard {
private:
    char board[8][8];

    bool _gameOver = false;

    std::vector<ChessPiece*> pieces;
public:
    ChessBoard();
    ~ChessBoard();
    void resetBoard();
    void printBoard();
    ChessPiece* getPiece(int x, int y) const;
    bool movePiece(int fromX, int fromY, int toX, int toY, const bool isWhite);

    bool isGameOver() const { return _gameOver; }
    void setGameOver() { _gameOver = true; }

    std::string xyToChessPos(int x, int y) const;
};