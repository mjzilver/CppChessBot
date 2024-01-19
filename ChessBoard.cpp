#include "ChessBoard.h"
#include <iostream> 

#include "ChessPiece.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/Pawn.h"

ChessBoard::ChessBoard()
{
    resetBoard();
}

void ChessBoard::resetBoard()
{
    pieces.clear();

    // Set up the board
    // Black pieces
    pieces.push_back(new Rook(0, 0, false));
    pieces.push_back(new Knight(1, 0, false));
    pieces.push_back(new Bishop(2, 0, false));
    pieces.push_back(new Queen(3, 0, false));
    pieces.push_back(new King(4, 0, false));
    pieces.push_back(new Bishop(5, 0, false));
    pieces.push_back(new Knight(6, 0, false));
    pieces.push_back(new Rook(7, 0, false));

    for (int i = 0; i < 8; ++i) {
        pieces.push_back(new Pawn(i, 1, false));
    }

    // White pieces
    pieces.push_back(new Rook(0, 7, true));
    pieces.push_back(new Knight(1, 7, true));
    pieces.push_back(new Bishop(2, 7, true));
    pieces.push_back(new Queen(3, 7, true));
    pieces.push_back(new King(4, 7, true));
    pieces.push_back(new Bishop(5, 7, true));
    pieces.push_back(new Knight(6, 7, true));
    pieces.push_back(new Rook(7, 7, true));

    for (int i = 0; i < 8; ++i) {
        pieces.push_back(new Pawn(i, 6, true));
    }
}

void ChessBoard::printBoard()
{
    // Output the board to the console
    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << ' ';
        for (int j = 0; j < 8; ++j) {
            auto piece = getPiece(j, i);
            if (piece == nullptr) {
                // No piece at this location
                std::cout << ' ';
            }
            else {
                std::cout << piece->getSymbol();
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

ChessPiece* ChessBoard::getPiece(int x, int y) const
{   
    // Error checking
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
    {
        return nullptr;
    }
    
    // loop vector
    for (int i = 0; i < pieces.size(); ++i)
    {
        if (pieces[i]->getX() == x && pieces[i]->getY() == y)
        {
            return pieces[i];
        }
    }
    return nullptr;
}

bool ChessBoard::movePiece(int fromX, int fromY, int toX, int toY)
{
    // Get the piece at the from coordinates
    ChessPiece* piece = getPiece(fromX, fromY);

    // validate move
    if (piece == nullptr)
    {
        return false;
    }

    // move to new location 
    piece->setX(toX);
    piece->setY(toY);    

    return true;
}

void ChessBoard::letterToIndex(char letter, int &index)
{
    switch (letter)
    {
    case 'a':
        index = 0;
        break;
    case 'b':
        index = 1;
        break;
    case 'c':
        index = 2;
        break;
    case 'd':
        index = 3;
        break;
    case 'e':
        index = 4;
        break;
    case 'f':
        index = 5;
        break;
    case 'g':
        index = 6;
        break;
    case 'h':
        index = 7;
        break;
    default:
        index = -1;
        break;
    }
}
