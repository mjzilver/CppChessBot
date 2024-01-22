#pragma once

#include "../ChessBoard.h"
#include "../ChessPiece.h"
#include "IDisplay.h"
#include <SFML/Graphics.hpp>
#include <map>

class GDisplay : public IDisplay
{
public:
    GDisplay();
    ~GDisplay();

    void drawBoard(const ChessBoard &board) override;
    void drawLoop(ChessBoard &board) override;
    void handleInput(ChessBoard &board) override;

private:
    sf::RenderWindow window;
    int squareSize;
    int margin;
    std::map<char, sf::Texture> pieceTextures;
    sf::Font font;
    ChessPiece* selectedPiece = nullptr;

    void loadPieceTextures(std::map<char, sf::Texture> &pieceTextures) const;
    void handleMouseClick(sf::Event::MouseButtonEvent &mouse, ChessBoard &board);
    void handleValidChessboardClick(int colIndex, int rowIndex, ChessBoard &board);
    void handleSelectedPieceClick(ChessPiece *clickedPiece, int colIndex, int rowIndex, ChessBoard &board);
    void handleMoveToOccupiedSquare(ChessPiece *clickedPiece, int colIndex, int rowIndex, ChessBoard &board);
    void handleMoveToEmptySquare(int colIndex, int rowIndex, ChessBoard &board);

    void handleEvent(sf::Event &event, ChessBoard &board);

    bool isCurrentPlayerWhite = true;
};
