#pragma once

#include "../ChessBoard.h"
#include <string>

class IDisplay {
public:
    virtual ~IDisplay() = default;
    virtual void displayBoard(const ChessBoard& board) = 0;
    virtual std::string receiveInput() = 0;
    virtual void drawLoop(ChessBoard& board) = 0;
};