#pragma once

class ChessBoard;  // forward declaration

class ChessPiece {
protected:
    int x;
    int y;
    int price = 0;
    bool isWhite;

public:
    ChessPiece(int x, int y, bool isWhite, int price);

    // deep copy constructor
    virtual ChessPiece* clone() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }
    int getPrice() const { return price; }

    virtual char getSymbol() const { return 'X'; };

    bool getIsWhite() const { return isWhite; }

    virtual void moveTo(int toX, int toY);

    virtual bool canMoveTo(int toX, int toY, const ChessBoard* board);

    virtual bool canAttack(int x, int y, const ChessBoard* board);
};
