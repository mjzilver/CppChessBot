#include "Player.h"

#include <iostream>

bool Player::makeMove(ChessBoard& board, const std::string& moveInput)
{
    if (moveInput.size() != 5 
        || !isalpha(moveInput[0]) 
        || !isdigit(moveInput[1]) 
        || !isalpha(moveInput[3]) 
        || !isdigit(moveInput[4])
    )
    {
        std::cout << "Invalid move format. Please use the format 'A2-A4'." << std::endl;
        return false;
    }

    // Convert input to coordinates
    int fromX = toupper(moveInput[0]) - 'A';
    int fromY = '8' - moveInput[1];  
    int toX = toupper(moveInput[3]) - 'A';
    int toY = '8' - moveInput[4]; 

    // Validate coordinates
    if (fromX < 0 || fromX >= 8 || fromY < 0 || fromY >= 8 ||
        toX < 0 || toX >= 8 || toY < 0 || toY >= 8)
    {
        std::cout << "Invalid coordinates. Coordinates must be within the range A1-H8." << std::endl;
        return false;
    }

    if(board.movePiece(fromX, fromY, toX, toY)) {
        return true;
    } else {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }
}