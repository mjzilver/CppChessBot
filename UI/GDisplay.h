#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "../ChessBoard.h"
#include "../ChessPiece.h"
#include "IDisplay.h"

class GDisplay : public IDisplay {
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
    ChessPiece *selectedPiece = nullptr;
    bool isCurrentPlayerWhite = true;

    void loadPieceTextures(std::map<char, sf::Texture> &pieceTextures) const;

    // Drawing functions
    void drawSquare(int x, int y, const sf::Color &color);
    void drawCircleOutline(int x, int y, float borderFraction, const sf::Color &borderColor);
    void drawCircle(int x, int y, float circleFraction, const sf::Color &color);

    // Event handlers for selecting and moving pieces
    void handleEvent(sf::Event &event, ChessBoard &board);
    void handleMouseClick(sf::Event::MouseButtonEvent &mouse, ChessBoard &board);
    void handleValidChessboardClick(int colIndex, int rowIndex, ChessBoard &board);
    void handleSelectedPieceClick(ChessPiece *clickedPiece, int colIndex, int rowIndex, ChessBoard &board);
    void handleMoveToOccupiedSquare(ChessPiece *clickedPiece, int colIndex, int rowIndex, ChessBoard &board);
    void handleMoveToEmptySquare(int colIndex, int rowIndex, ChessBoard &board);
};
