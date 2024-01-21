#pragma once

#include <vector>
#include <string>

#include "ChessBoard.h"
#include "ChessPiece.h"

class Player
{
public:
    Player(bool isWhite) : isWhite(isWhite) {}
    bool makeMove(ChessBoard &board, const std::string &moveInput);

private:
    std::vector<ChessPiece *> pieces;
    bool isWhite;
};
