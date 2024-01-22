#pragma once

#include "ChessBoard.h"
#include "ChessGUI.h"

class ChessGame
{
private:
    ChessBoard board;
    ChessGUI* chessGUI;
public:
    ChessGame();
    ~ChessGame();

    void startGame(bool with_gui);
    void displayBoard();
    std::string receiveInput();
};
