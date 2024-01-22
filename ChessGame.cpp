#include "ChessGame.h"
#include "Pieces/Pawn.h"
#include "UI/GDisplay.h"

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
    if (gDisplay != nullptr) delete gDisplay;
}

void ChessGame::startGame(bool with_gui)
{
    std::thread* guiThread = nullptr;

    if (with_gui)
    {
        gDisplay = new GDisplay();
        guiThread = new std::thread(&GDisplay::drawLoop, gDisplay, std::ref(board));   
    } 

    IDisplay* display = new ConsoleDisplay();
    
    while(board.isGameOver() == false)
    {
        display->drawLoop(board);
    }

    std::cout << "Game over!" << std::endl;
    guiThread->join();
    delete guiThread;
}