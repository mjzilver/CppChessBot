#include "ConsoleDisplay.h"

#include <iostream>

void ConsoleDisplay::displayBoard(const ChessBoard& board) {
    std::cout << "  ";
    for (int i = 0; i < 8; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 8; j++) {
            std::cout << board.getPiece(i, j)->getSymbol() << " ";
        }
        std::cout << std::endl;
    }
}

std::string ConsoleDisplay::receiveInput() {
    std::string input;
    std::cin >> input;
    return input;
}

void ConsoleDisplay::drawLoop(ChessBoard &board)
{
    while (board.isGameOver() == false)
    {
        std::cout << "Player 1's turn (white): " << std::endl;
        std::string moveInputPlayer1 = receiveInput();
        while (makeMove(board, moveInputPlayer1, true))
        {
            moveInputPlayer1 = receiveInput();
            displayBoard(board);
        }
        displayBoard(board);

        std::string moveInputPlayer2 = receiveInput();
        while (makeMove(board, moveInputPlayer2, false))
        {
            moveInputPlayer2 = receiveInput();
            displayBoard(board);
        }
        displayBoard(board);
    }

    std::cout << "Game over!" << std::endl;
}

bool ConsoleDisplay::makeMove(ChessBoard &board, const std::string &moveInput, bool isWhite)
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

    if (board.movePiece(fromX, fromY, toX, toY, isWhite, moveInput.size() == 5 ? moveInput[4] : 'Q'))
    {
        return true;
    }
    else
    {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }
}
