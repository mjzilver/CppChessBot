#pragma once

class ChessBoard;  // forward declaration

class ChessPiece {
protected:
    int x;
    int y;
    int price = 0;
    const bool isWhite;

public:
    ChessPiece(int x, int y, bool isWhite, int price);

    // deep copy constructor
    ChessPiece(const ChessPiece& other) : x(other.x), y(other.y), isWhite(other.isWhite), price(other.price) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getPrice() const { return price; }

    virtual char getSymbol() const { return ' '; };

    bool getIsWhite() const { return isWhite; }

    virtual void moveTo(int toX, int toY);

    virtual bool canMoveTo(int toX, int toY, const ChessBoard* board);

    virtual bool canAttack(int x, int y, const ChessBoard* board);
};
