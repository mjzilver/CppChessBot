#include "ChessPiece.h"

#include "ChessBoard.h"

ChessPiece::ChessPiece(int x, int y, bool isWhite) : x(x), y(y), isWhite(isWhite) {}

void ChessPiece::moveTo(int toX, int toY) {
    x = toX;
    y = toY;
}

bool ChessPiece::canMoveTo(int toX, int toY, const ChessBoard* board) {
    if (board->getPiece(toX, toY) != nullptr && board->getPiece(toX, toY)->getIsWhite() == isWhite) return false;
    if (toX == x && toY == y) return false;
    return true;
}

bool ChessPiece::canAttack(int x, int y, const ChessBoard* board) { return canMoveTo(x, y, board); }
