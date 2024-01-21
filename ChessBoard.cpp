#include "ChessBoard.h"
#include <iostream>

#include "ChessPiece.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/Pawn.h"

#include <algorithm>

ChessBoard::ChessBoard()
{
}

void ChessBoard::resetBoard()
{
    for (int i = 0; i < pieces.size(); ++i)
    {
        delete pieces[i];
    }

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

    for (int i = 0; i < 8; ++i)
    {
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

    for (int i = 0; i < 8; ++i)
    {
        pieces.push_back(new Pawn(i, 6, true));
    }
}

void ChessBoard::printBoard()
{
    // Output the board to the console
    for (int i = 0; i < 8; ++i)
    {
        std::cout << 8 - i << ' ';
        for (int j = 0; j < 8; ++j)
        {
            auto piece = getPiece(j, i);
            if (piece == nullptr)
            {
                // No piece at this location
                std::cout << ' ';
            }
            else
            {
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

ChessBoard::~ChessBoard()
{
    for (int i = 0; i < pieces.size(); ++i)
    {
        delete pieces[i];
    }
}

std::string ChessBoard::xyToChessPos(int x, int y) const
{
    std::string chessPos = "";
    chessPos += (char)(x + 'A');
    chessPos += (char)('8' - y);
    return chessPos;
}

bool ChessBoard::movePiece(int fromX, int fromY, int toX, int toY, bool isWhite)
{
    // Get the piece at the from coordinates
    ChessPiece* piece = getPiece(fromX, fromY);

    // validate move
    if (piece == nullptr)
    {
        std::cout << "No piece at position (" << xyToChessPos(fromX, fromY) << ")" << std::endl;
        return false;
    }

    if (piece->getIsWhite() != isWhite)
    {
        std::cout << "Piece at position (" << xyToChessPos(fromX, fromY) << ") is not your color" << std::endl;
        return false;
    }

    // check if there is a piece at the to coordinates
    ChessPiece* pieceAtTo = getPiece(toX, toY);
    if (pieceAtTo != nullptr)
    {
        // check if the piece at the to coordinates is the same color as the piece at the from coordinates
        if (pieceAtTo->getIsWhite() == piece->getIsWhite())
        {
            std::cout << "Piece at position (" << xyToChessPos(toX, toY) << ") is the same color as the piece at position (" << xyToChessPos(fromX, fromY) << ")" << std::endl;
            return false;
        }
        else if (piece->canAttack(toX, toY))
        {
            pieces.erase(std::remove(pieces.begin(), pieces.end(), pieceAtTo), pieces.end());
        }
        else
        {
            std::cout << "Piece at position (" << xyToChessPos(fromX, fromY) << ") cannot attack the piece at position (" << xyToChessPos(toX, toY) << ")" << std::endl;
            return false;
        }
    }
    else if (!piece->canMoveTo(toX, toY, this))
    {
        std::cout << "Piece at position (" << xyToChessPos(fromX, fromY) << ") cannot move to position (" << xyToChessPos(toX, toY) << ")" << std::endl;
        return false;
    } 

    // move to new location
    piece->setX(toX);
    piece->setY(toY);

    return true;
}
