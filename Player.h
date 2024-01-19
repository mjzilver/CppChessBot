#pragma once

#include <vector>
#include <string>

#include "ChessBoard.h"
#include "ChessPiece.h"

class Player {
public:
    bool makeMove(ChessBoard& board, const std::string& moveInput);

private:
    std::vector<ChessPiece*> pieces;
};
