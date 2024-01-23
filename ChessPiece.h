#pragma once

class ChessBoard;  // forward declaration

class ChessPiece {
protected:
    int x;
    int y;
    bool isWhite;

public:
    ChessPiece(int x, int y, bool isWhite) : x(x), y(y), isWhite(isWhite) {}

    // deep copy constructor
    virtual ChessPiece* clone() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }

    virtual char getSymbol() const = 0;

    bool getIsWhite() const { return isWhite; }

    virtual void moveTo(int toX, int toY);

    virtual bool canMoveTo(int toX, int toY, const ChessBoard* board);

    virtual bool canAttack(int x, int y, const ChessBoard* board);
};
