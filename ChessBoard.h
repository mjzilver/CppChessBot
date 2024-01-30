#pragma once

#include <string>
#include <vector>

#include "ChessPiece.h"

class ChessBoard {
private:
    bool _gameOver = false;

    std::vector<ChessPiece *> pieces = std::vector<ChessPiece *>();

public:
    ChessBoard();
    // deep copy constructor
    ChessBoard(const ChessBoard &other) : _gameOver(other._gameOver) {
        for (int i = 0; i < other.pieces.size(); ++i) {
            pieces.push_back(other.pieces[i]->clone());
        }
    }
    ~ChessBoard();

    // board functions
    void resetBoard();
    void emptyBoard() {
        for (int i = 0; i < pieces.size(); ++i) {
            delete pieces[i];
        }
        pieces.clear();
    }

    // piece functions
    ChessPiece *getPiece(int x, int y) const;
    std::vector<ChessPiece *> getPieces() const { return pieces; }
    void addPiece(ChessPiece *piece) { pieces.push_back(piece); }
    bool movePiece(int fromX, int fromY, int toX, int toY, const bool isWhite, char promoteTo = 'Q');
    bool removePiece(int x, int y);
    bool removePiece(ChessPiece *piece);
    bool promotePiece(ChessPiece *piece, char promoteTo, int toX, int toY);

    // game functions
    bool isGameOver() const { return _gameOver; }
    void setGameOver() { _gameOver = true; }

    // helper functions
    std::string xyToChessPos(int x, int y) const;
};