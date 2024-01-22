#include "ChessGame.h"
#include "Pieces/Pawn.h"
#include "ChessGUI.h"

#include <iostream>
#include <thread>
#include <functional>

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

    std::thread* chessGUIThread = nullptr;

    if (with_gui)
    {
        chessGUI = new ChessGUI();
        std::cout << "GUI is enabled" << std::endl;
        chessGUIThread = new std::thread(&ChessGUI::drawLoop, chessGUI, std::ref(board));   
    }

    while (board.isGameOver() == false)
    {
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

    std::cout << "Game over!" << std::endl;
    chessGUIThread->join();
    delete chessGUIThread;
}

void ChessGame::displayBoard()
{
    board.printBoard();
}

std::string ChessGame::receiveInput()
{
    std::string input;
    std::cout << "Enter your move:";
    std::cin >> input;
    return input;
}