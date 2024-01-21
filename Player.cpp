#include "Player.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"

#include <iostream>

bool Player::makeMove(ChessBoard &board, const std::string &moveInput)
{
    if ((moveInput.size() < 4 || moveInput.size() > 5) || !isalpha(moveInput[0]) || !isdigit(moveInput[1]) || !isalpha(moveInput[2]) || !isdigit(moveInput[3]))
    {
        std::cout << "Invalid move format. Please use the format 'a2a4'." << std::endl;
        return false;
    }

    // Convert input to coordinates
    int fromX = tolower(moveInput[0]) - 'a';
    int fromY = '8' - moveInput[1];
    int toX = tolower(moveInput[2]) - 'a';
    int toY = '8' - moveInput[3];

    // Validate coordinates
    if (fromX < 0 || fromX >= 8 || fromY < 0 || fromY >= 8 ||
        toX < 0 || toX >= 8 || toY < 0 || toY >= 8)
    {
        std::cout << "Invalid coordinates. Coordinates must be within the range a1 to h8." << std::endl;
        return false;
    }

    std::cout << "Moving from " << moveInput[0] << moveInput[1] << " to " << moveInput[2] << moveInput[3] << std::endl;
    std::cout << "From: " << fromX << ", " << fromY << std::endl;
    std::cout << "To: " << toX << ", " << toY << std::endl;

    if (toY == 7 || toY == 0)
    {
        auto piece = board.getPiece(fromX, fromY);

        if (
            piece != nullptr && piece->canMoveTo(toX, toY, &board) &&
            ((piece->getSymbol() == 'P' && toY == 0) || (piece->getSymbol() == 'p' && toY == 7)))
        {
            if (moveInput.size() == 5)
            {
                switch (moveInput[4])
                {
                case 'Q':
                    board.addPiece(new Queen(toX, toY, isWhite));
                    break;
                case 'R':
                    board.addPiece(new Rook(toX, toY, isWhite));
                    break;
                case 'B':
                    board.addPiece(new Bishop(toX, toY, isWhite));
                    break;
                case 'N':
                    board.addPiece(new Knight(toX, toY, isWhite));
                    break;
                default:
                    std::cout << "Invalid promotion. Please promote to Q, R, B, or N." << std::endl;
                    return false;
                }

                // remove pawn after promotion
                if (board.removePiece(fromX, fromY))
                {
                    return true;
                }
                else
                {
                    std::cout << "Underable to remove Piece. Memory leaking." << std::endl;
                    return false;
                }
            }
            else
            {
                std::cout << "Invalid promotion. Please specify what to promote to Q, R, B, or N." << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "Something is wrong here." << std::endl;
            std::cout << "Piece: " << piece->getSymbol() << std::endl;
            std::cout << "Can move: " << piece->canMoveTo(toX, toY, &board) << std::endl;
            return false;
        }
    }

    if (board.movePiece(fromX, fromY, toX, toY, isWhite))
    {
        return true;
    }
    else
    {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }
}