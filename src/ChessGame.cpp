#include "ChessGame.h"

#include <functional>
#include <iostream>
#include <thread>

#include "UI/GDisplay.h"

ChessGame::ChessGame() : board() {
    board.resetBoard();
}

ChessGame::~ChessGame() {
    if (display != nullptr) delete display;
}

void ChessGame::startGame(const bool with_gui) {
    AI ai(5);

    if (with_gui) {
        display = new GDisplay(&ai);
    } else {
        display = new ConsoleDisplay();
    }

    display->drawLoop(board);

    std::cout << "Game over!" << std::endl;
}