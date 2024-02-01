#include "ChessGame.h"

#include <functional>
#include <iostream>
#include <thread>

#include "UI/GDisplay.h"

ChessGame::ChessGame() : board() {
    // set the board
    board.resetBoard();
}

ChessGame::~ChessGame() {
    if (gDisplay != nullptr) delete gDisplay;
}

void ChessGame::startGame(bool with_gui) {
    IDisplay* display;

    if (with_gui) {
        display = new GDisplay();
    } else {
        display = new ConsoleDisplay();
    }

    display->drawLoop(board);

    std::cout << "Game over!" << std::endl;
}