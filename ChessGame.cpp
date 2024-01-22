#include "ChessGame.h"
#include "Pieces/Pawn.h"
#include "ChessGUI.h"

#include <iostream>

ChessGame::ChessGame()
    : board(), player1(true), player2(false)
{
    // set the board
    board.resetBoard();
}

ChessGame::~ChessGame()
{
    if (chessGUI != nullptr) delete chessGUI;
}

void ChessGame::startGame(bool with_gui)
{
    board.printBoard();

    if (with_gui)
    {
        chessGUI = new ChessGUI();
        std::cout << "GUI is enabled" << std::endl;
    }

    while (board.isGameOver() == false)
    {
        displayBoard();
        std::cout << "Player 1's turn (white): " << std::endl;
        std::string moveInputPlayer1 = receiveInput();
        while (!player1.makeMove(board, moveInputPlayer1))
        {
            moveInputPlayer1 = receiveInput();
            displayBoard();
        }
        displayBoard();

        std::cout << "Player 2's turn (black): " << std::endl;
        std::string moveInputPlayer2 = receiveInput();
        while (!player2.makeMove(board, moveInputPlayer2))
        {
            moveInputPlayer2 = receiveInput();
            displayBoard();
        }
        displayBoard();
    }
}

void ChessGame::displayBoard()
{
    if (chessGUI != nullptr)
    {
        chessGUI->drawBoard(board);
    }

    board.printBoard();
}

std::string ChessGame::receiveInput()
{
    std::string input;
    std::cout << "Enter your move:";
    std::cin >> input;
    return input;
}