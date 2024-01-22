#pragma once

#include "IDisplay.h"

class ConsoleDisplay : public IDisplay {
public:
    void displayBoard(const ChessBoard& board) override;
    std::string receiveInput() override;
    void drawLoop(ChessBoard& board) override;
    bool makeMove(ChessBoard &board, const std::string &moveInput, bool isWhite);
};