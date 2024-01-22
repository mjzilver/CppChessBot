#pragma once

#include "ChessBoard.h"
#include <SFML/Graphics.hpp>
#include <map>

class ChessGUI
{
public:
    ChessGUI();
    ~ChessGUI();

    void drawBoard(const ChessBoard &board);

private:
    sf::RenderWindow window;
    int squareSize;
    int margin;
    std::map<char, sf::Texture> pieceTextures;
    sf::Font font;

    void loadPieceTextures(std::map<char, sf::Texture> &pieceTextures) const;
};
