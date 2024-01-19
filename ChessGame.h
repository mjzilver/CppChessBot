#pragma once

#include "ChessBoard.h"
#include "Player.h"

class ChessGame {
private:
    ChessBoard board;
    Player player1;
    Player player2;

public:
    ChessGame();

    void startGame();
    std::string receiveInput();
};
