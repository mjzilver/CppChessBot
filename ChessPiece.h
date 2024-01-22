#pragma once

class ChessBoard; // forward declaration

class ChessPiece
{
protected:
    int x;
    int y;
    const bool isWhite;

public:
    ChessPiece(int x, int y, bool isWhite) : x(x), y(y), isWhite(isWhite){};

    int getX() const { return x; }
    int getY() const { return y; }

    virtual char getSymbol() const = 0;

    bool getIsWhite() const { return isWhite; }

    virtual void moveTo(int toX, int toY)
    {
        x = toX;
        y = toY;
    }

    virtual bool canMoveTo(int x, int y, ChessBoard *board) = 0;
    // only pawns can attack differently than they move so rest uses canMoveTo
    virtual bool canAttack(int x, int y, ChessBoard *board) { return canMoveTo(x, y, board); }

    virtual ~ChessPiece() = default;
};