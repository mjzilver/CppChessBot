#pragma once

class ChessPiece {
protected:
    int x;
    int y;
    bool isWhite;
public:
    ChessPiece(int x, int y, bool isWhite);

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    virtual char getSymbol() = 0;
};