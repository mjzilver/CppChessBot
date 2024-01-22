#include "ChessGame.h"
#include "Pieces/Pawn.h"
#include "ChessGUI.h"

#include <iostream>
#include <thread>
#include <functional>

ChessGame::ChessGame()
    : board()
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
    std::thread* chessGUIThread = nullptr;

    if (with_gui)
    {
        chessGUI = new ChessGUI();
        chessGUIThread = new std::thread(&ChessGUI::drawLoop, chessGUI, std::ref(board));   
    }

    while (board.isGameOver() == false)
    {

        displayBoard();
    }

    std::cout << "Game over!" << std::endl;
    chessGUIThread->join();
    delete chessGUIThread;
}

void ChessGame::displayBoard()
{

}

std::string ChessGame::receiveInput()
{
    std::string input;
    std::cout << "Enter your move:";
    std::cin >> input;
    return input;
}