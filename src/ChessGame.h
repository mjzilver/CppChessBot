#pragma once

#include "ChessBoard.h"
#include "UI/ConsoleDisplay.h"
#include "UI/GDisplay.h"

class ChessGame {
private:
    ChessBoard board;
    IDisplay* display = nullptr;

public:
    ChessGame();
    ~ChessGame();

    void startGame(const bool with_gui);
};
