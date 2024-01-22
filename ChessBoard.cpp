#include "ChessBoard.h"

#include "ChessPiece.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/Pawn.h"

#include <algorithm>
#include <iostream>

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


ChessPiece *ChessBoard::getPiece(int x, int y) const
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
    chessPos += (char)(x + 'a');
    chessPos += (char)('8' - y);
    return chessPos;
}

bool ChessBoard::movePiece(int fromX, int fromY, int toX, int toY, bool isWhite, char promoteTo)
{
    // if coords are outside of board, return false
    if (fromX < 0 || fromX >= 8 || fromY < 0 || fromY >= 8 || toX < 0 || toX >= 8 || toY < 0 || toY >= 8)
    {
        return false;
    }

    // Get the piece at the from coordinates
    ChessPiece *piece = getPiece(fromX, fromY);

    // validate move
    if (piece == nullptr)
    {
        return false;
    }

    if (piece->getIsWhite() != isWhite)
    {
        return false;
    }

    // check if there is a piece at the to coordinates
    ChessPiece *pieceAtTo = getPiece(toX, toY);
    if (pieceAtTo != nullptr)
    {
        // check if the piece at the to coordinates is the same color as the piece at the from coordinates
        if (pieceAtTo->getIsWhite() == piece->getIsWhite())
        {
            return false;
        }
        else if (piece->canAttack(toX, toY, this))
        {
            pieces.erase(std::remove(pieces.begin(), pieces.end(), pieceAtTo), pieces.end());
            delete pieceAtTo;
        }
        else
        {
            return false;
        }
    }
    else if (!piece->canMoveTo(toX, toY, this))
    {
        return false;
    }


    // if pawn reaches end of board, promote to queen
    if (piece->getSymbol() == 'P' && toY == 0 || piece->getSymbol() == 'p' && toY == 7) {
        return promotePiece(piece, promoteTo, toX, toY);
    } else {
        piece->moveTo(toX, toY);
        return true;
    }
}

bool ChessBoard::removePiece(int x, int y)
{
    ChessPiece *piece = getPiece(x, y);
    return removePiece(piece);
}

bool ChessBoard::removePiece(ChessPiece *piece)
{
    if (piece == nullptr)
    {
        return false;
    }

    pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
    delete piece;
    return true;
}

bool ChessBoard::promotePiece(ChessPiece *piece, char promoteTo, int toX, int toY)
{
    if (piece == nullptr)
    {
        return false;
    }

    switch (toupper(promoteTo))
    {
    case 'Q':
        pieces.push_back(new Queen(toX, toY, piece->getIsWhite()));
        break;
    case 'R':
        pieces.push_back(new Rook(toX, toY, piece->getIsWhite()));
        break;
    case 'B':
        pieces.push_back(new Bishop(toX, toY, piece->getIsWhite()));
        break;
    case 'N':   
        pieces.push_back(new Knight(toX, toY, piece->getIsWhite()));
        break;
    default:
        return false;
    }

    removePiece(piece);

    return true;
}
