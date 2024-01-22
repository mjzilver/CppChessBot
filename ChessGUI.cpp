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

void ChessGUI::drawBoard(const ChessBoard &board)
{
    std::cout << "Drawing board" << std::endl;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

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
        {'P', "WP.png"}, {'N', "WN.png"}, {'B', "WB.png"}, {'R', "WR.png"}, {'Q', "WQ.png"}, {'K', "WK.png"}, {'p', "BP.png"}, {'n', "BN.png"}, {'b', "BB.png"}, {'r', "BR.png"}, {'q', "BQ.png"}, {'k', "BK.png"}};

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
