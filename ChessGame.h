#pragma once

#include "ChessBoard.h"
#include "UI/GDisplay.h"
#include "UI/ConsoleDisplay.h"

class ChessGame
{
private:
    ChessBoard board;
    GDisplay* gDisplay;
public:
    ChessGame();
    ~ChessGame();

    void startGame(bool with_gui);
};
