#pragma once

#include "../ChessBoard.h"
#include <string>

class IDisplay {
public:
    virtual ~IDisplay() = default;
    virtual void drawBoard(const ChessBoard& board) = 0;
    virtual void drawLoop(ChessBoard& board) = 0;
};