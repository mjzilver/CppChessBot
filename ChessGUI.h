#pragma once

#include "ChessBoard.h"
#include "ChessPiece.h"
#include <SFML/Graphics.hpp>
#include <map>

class ChessGUI
{
public:
    ChessGUI();
    ~ChessGUI();

    void drawBoard(ChessBoard &board);
    void drawLoop(ChessBoard &board);

private:
    sf::RenderWindow window;
    int squareSize;
    int margin;
    std::map<char, sf::Texture> pieceTextures;
    sf::Font font;
    ChessPiece* selectedPiece = nullptr;

    void loadPieceTextures(std::map<char, sf::Texture> &pieceTextures) const;
    void handleMouseClick(sf::Event::MouseButtonEvent &mouse, ChessBoard &board);
    void handleEvent(sf::Event &event, ChessBoard &board);
};
