#include "ChessGame.h"

#include <iostream>

ChessGame::ChessGame()
: board(), player1(true), player2(false)
{
    // set the board
    board.resetBoard();
}

void ChessGame::startGame()
{
    board.printBoard();

    while (board.isGameOver() == false)
    {
        std::cout << "Player 1's turn (white): " << std::endl;
        std::string moveInputPlayer1 = receiveInput();
        while(!player1.makeMove(board, moveInputPlayer1))
        {
            moveInputPlayer1 = receiveInput();
        }
        board.printBoard();

        std::cout << "Player 2's turn (black): " << std::endl;
        std::string moveInputPlayer2 = receiveInput();
        while(!player2.makeMove(board, moveInputPlayer2))
        {
            moveInputPlayer2 = receiveInput();
        }
        board.printBoard();
    }
}

std::string ChessGame::receiveInput()
{
    std::string input;
    std::cout << "Enter your move:";
    std::cin >> input;
    return input;
}