#pragma once

#include "IDisplay.h"

class ConsoleDisplay : public IDisplay {
public:
    void drawBoard(const ChessBoard& board) override;
    std::string receiveInput();
    void drawLoop(ChessBoard& board) override;
    bool makeMove(ChessBoard& board, const std::string& moveInput);
    void handleInput(ChessBoard& board) override;
};