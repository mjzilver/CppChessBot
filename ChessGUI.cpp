#include "ChessGUI.h"
#include <SFML/Graphics.hpp>
#include <iostream>

ChessGUI::ChessGUI() : window(sf::VideoMode(500u, 500u), "Chess Game"), squareSize(60), margin(25)
{
    loadPieceTextures(pieceTextures);
    if (!font.loadFromFile("../resources/OpenSans-Regular.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
}

ChessGUI::~ChessGUI()
{
    pieceTextures.clear();
}

void ChessGUI::drawLoop(ChessBoard &board)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            handleEvent(event, board);
        }

        drawBoard(board);
    }
}

void ChessGUI::drawBoard(ChessBoard &board)
{
    window.clear();

    // Draw ranks
    for (int i = 0; i < 8; ++i)
    {
        sf::Text rankLabel(std::to_string(8 - i), font, 20);
        rankLabel.setPosition(5, i * squareSize + (margin));
        rankLabel.setFillColor(sf::Color::White);
        window.draw(rankLabel);
    }

    // Draw files
    for (int i = 0; i < 8; ++i)
    {
        sf::Text fileLabel(std::string(1, 'A' + i), font, 20);
        fileLabel.setPosition(i * squareSize + (margin * 2), squareSize * 8);
        fileLabel.setFillColor(sf::Color::White);
        window.draw(fileLabel);
    }

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            // draw white or black square
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(j * squareSize + margin, i * squareSize);
            if ((i + j) % 2 == 0)
            {
                square.setFillColor(sf::Color(255, 255, 255));
            }
            else
            {
                square.setFillColor(sf::Color(70, 70, 70));
            }
            window.draw(square);

            // draw piece on square
            auto piece = board.getPiece(j, i);
            if (piece == nullptr)
            {
                continue;
            }
            else
            {
                char pieceSymbol = piece->getSymbol();

                auto it = pieceTextures.find(pieceSymbol);
                if (it != pieceTextures.end())
                {
                    // draw a border around the selected piece
                    if(selectedPiece != nullptr && piece == selectedPiece) {
                        sf::CircleShape border(squareSize / 2);
                        border.setPosition(j * squareSize + margin, i * squareSize);
                        border.setFillColor(sf::Color::Transparent);
                        border.setOutlineThickness(2);
                        border.setOutlineColor(sf::Color::Black);
                        window.draw(border);
                    }

                    sf::Sprite pieceSprite(it->second);
                    pieceSprite.setPosition(j * squareSize + margin, i * squareSize);
                    window.draw(pieceSprite);
                }
                else
                {
                    std::cerr << "Texture not found for piece " << piece << std::endl;
                }
            }
        }
    }

    window.display();
}

void ChessGUI::loadPieceTextures(std::map<char, sf::Texture> &pieceTextures) const
{
    const std::string imagePath = "../images/";

    // Define the pieces and their corresponding filenames
    std::map<char, std::string> pieceFilenames = {
        {'P', "WP.png"}, {'N', "WN.png"}, {'B', "WB.png"}, {'R', "WR.png"}, {'Q', "WQ.png"}, {'K', "WK.png"}, 
        {'p', "BP.png"}, {'n', "BN.png"}, {'b', "BB.png"}, {'r', "BR.png"}, {'q', "BQ.png"}, {'k', "BK.png"}};

    for (const auto &entry : pieceFilenames)
    {
        char piece = entry.first;
        const std::string &filename = entry.second;

        sf::Texture texture;
        if (texture.loadFromFile(imagePath + filename))
        {
            pieceTextures[piece] = texture;
        }
        else
        {
            std::cerr << "Error loading texture for piece " << piece << std::endl;
        }
    }
}

void ChessGUI::handleEvent(sf::Event &event, ChessBoard &board)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::MouseButtonPressed:
        handleMouseClick(event.mouseButton, board);
        break;
    default:
        break;
    }
}

void ChessGUI::handleMouseClick(sf::Event::MouseButtonEvent &mouse, ChessBoard &board)
{
    if (mouse.button == sf::Mouse::Left)
    {
        // Get the mouse position in window coordinates
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Convert window coordinates to view coordinates
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        // Convert view coordinates to board coordinates
        int col = (worldPos.x - margin) / squareSize;
        int row = (worldPos.y) / squareSize;

        if (col >= 0 && col < 8 && row >= 0 && row < 8)
        {
            auto clickedPiece = board.getPiece(col, row);
            if (selectedPiece != nullptr)
            {
                if(clickedPiece != nullptr) {
                    if (board.attack(selectedPiece, clickedPiece)) {
                        selectedPiece = nullptr;
                    } else {
                        selectedPiece = clickedPiece;
                    }
                } else if(selectedPiece->canMoveTo(col, row, &board)) {
                    board.movePiece(selectedPiece->getX(), selectedPiece->getY(), col, row, selectedPiece->getIsWhite());
                    selectedPiece = nullptr;
                } else {
                    selectedPiece = nullptr;
                }
            } else {
                selectedPiece = board.getPiece(col, row);
            }
        }
    }
}