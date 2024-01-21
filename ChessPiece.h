#pragma once

class ChessPiece {
protected:
    int x;
    int y;
    const bool isWhite;
public:
    ChessPiece(int x, int y, bool isWhite) : x(x), y(y), isWhite(isWhite) {};

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    virtual char getSymbol() const = 0;

    bool getIsWhite() const { return isWhite; }

    virtual bool canMoveTo(int x, int y) = 0;
    // only pawns can attack differently than they move so rest uses canMoveTo
    virtual bool canAttack(int x, int y) { return canMoveTo(x, y); }

    virtual ~ChessPiece() = default;
};