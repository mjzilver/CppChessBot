#include "ChessGame.h"

#include <iostream>

ChessGame::ChessGame()
: board(), player1(), player2()
{

}

void ChessGame::startGame()
{
    board.printBoard();

    while (true)
    {
        std::cout << "Player 1's turn" << std::endl;
        std::string moveInputPlayer1 = receiveInput();
        while(!player1.makeMove(board, moveInputPlayer1))
        {
            moveInputPlayer1 = receiveInput();
        }
        board.printBoard();

        // player 2 later
    }
}

std::string ChessGame::receiveInput()
{
    std::string input;
    std::cout << "Enter your move (e.g., A2-A4): ";
    std::cin >> input;
    return input;
}