#pragma once

#include "ChessBoard.h"
#include "ChessGUI.h"
#include "Player.h"

class ChessGame
{
private:
    ChessBoard board;
    Player player1;
    Player player2;
    ChessGUI* chessGUI;
public:
    ChessGame();
    ~ChessGame();

    void startGame(bool with_gui);
    void displayBoard();
    std::string receiveInput();
};
