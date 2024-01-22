#include "GDisplay.h"

#include <SFML/Graphics.hpp>
#include <iostream>

GDisplay::GDisplay() : window(sf::VideoMode(500u, 500u), "Chess Game"), squareSize(60), margin(25) {
    loadPieceTextures(pieceTextures);
    if (!font.loadFromFile("../resources/OpenSans-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    window.setView(window.getDefaultView());
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(true);
    window.setActive(true);
    window.clear();
    window.display();
}

GDisplay::~GDisplay() { pieceTextures.clear(); }

void GDisplay::drawLoop(ChessBoard &board) {
    while (window.isOpen()) {
        handleInput(board);

        drawBoard(board);
    }
}

void GDisplay::handleInput(ChessBoard &board) {
    sf::Event event;
    while (window.pollEvent(event)) {
        handleEvent(event, board);
    }
}

void GDisplay::drawBoard(const ChessBoard &board) {
    window.clear();

    // Draw ranks
    for (int i = 0; i < 8; ++i) {
        sf::Text rankLabel(std::to_string(8 - i), font, 20);
        rankLabel.setPosition(5, i * squareSize + (margin));
        rankLabel.setFillColor(sf::Color::White);
        window.draw(rankLabel);
    }

    // Draw files
    for (int i = 0; i < 8; ++i) {
        sf::Text fileLabel(std::string(1, 'A' + i), font, 20);
        fileLabel.setPosition(i * squareSize + (margin * 2), squareSize * 8);
        fileLabel.setFillColor(sf::Color::White);
        window.draw(fileLabel);
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0) {
                drawSquare(j, i, sf::Color(230, 230, 230));
            } else {
                drawSquare(j, i, sf::Color(75, 75, 75));
            }

            // if selected piece is not null, draw possible moves
            if (selectedPiece != nullptr) {
                if (board.getPiece(j, i) != nullptr && selectedPiece->canAttack(j, i, &board)) {
                    drawSquare(j, i, sf::Color(255, 0, 0, 100));
                } else if (selectedPiece->canMoveTo(j, i, &board)) {
                    drawCircle(j, i, 0.5, sf::Color(0, 255, 0, 100));
                }
            }

            // draw piece on square
            auto piece = board.getPiece(j, i);
            if (piece == nullptr) {
                continue;
            }

            char pieceSymbol = piece->getSymbol();

            auto it = pieceTextures.find(pieceSymbol);
            if (it != pieceTextures.end()) {
                // draw a circle around the selected piece
                if (selectedPiece != nullptr && piece == selectedPiece) {
                    drawCircleOutline(j, i, 0.8, sf::Color(0, 0, 255, 100));
                }

                sf::Sprite pieceSprite(it->second);
                pieceSprite.setPosition(j * squareSize + margin, i * squareSize);
                window.draw(pieceSprite);
            } else {
                std::cerr << "Texture not found for piece " << piece << std::endl;
            }
        }
    }

    window.display();
}

void GDisplay::loadPieceTextures(std::map<char, sf::Texture> &pieceTextures) const {
    const std::string imagePath = "../images/";

    // Define the pieces and their corresponding filenames
    std::map<char, std::string> pieceFilenames = {{'P', "WP.png"}, {'N', "WN.png"}, {'B', "WB.png"}, {'R', "WR.png"},
                                                  {'Q', "WQ.png"}, {'K', "WK.png"}, {'p', "BP.png"}, {'n', "BN.png"},
                                                  {'b', "BB.png"}, {'r', "BR.png"}, {'q', "BQ.png"}, {'k', "BK.png"}};

    for (const auto &entry : pieceFilenames) {
        char piece = entry.first;
        const std::string &filename = entry.second;

        sf::Texture texture;
        if (texture.loadFromFile(imagePath + filename)) {
            pieceTextures[piece] = texture;
        } else {
            std::cerr << "Error loading texture for piece " << piece << std::endl;
        }
    }
}

void GDisplay::drawCircleOutline(int x, int y, float circleFraction, const sf::Color &borderColor) {
    const float radius = circleFraction * (squareSize / 2);
    const float offset = (squareSize * (1 - circleFraction)) / 2;

    sf::CircleShape border(radius);
    border.setPosition(x * squareSize + margin + offset, y * squareSize + offset);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(4);
    border.setOutlineColor(borderColor);
    window.draw(border);
}

void GDisplay::drawCircle(int x, int y, float circleFraction, const sf::Color &color) {
    const float radius = circleFraction * (squareSize / 2);
    const float offset = (squareSize * (1 - circleFraction)) / 2;

    sf::CircleShape circle(radius);
    circle.setPosition(x * squareSize + margin + offset, y * squareSize + offset);
    circle.setFillColor(color);
    window.draw(circle);
}

void GDisplay::drawSquare(int x, int y, const sf::Color &color) {
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
    square.setPosition(x * squareSize + margin, y * squareSize);
    square.setFillColor(color);
    window.draw(square);
}

void GDisplay::handleEvent(sf::Event &event, ChessBoard &board) {
    switch (event.type) {
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

void GDisplay::handleMouseClick(sf::Event::MouseButtonEvent &mouse, ChessBoard &board) {
    if (mouse.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f viewCoordinates = window.mapPixelToCoords(mousePos);

        int colIndex = static_cast<int>((viewCoordinates.x - margin) / squareSize);
        int rowIndex = static_cast<int>(viewCoordinates.y / squareSize);

        handleValidChessboardClick(colIndex, rowIndex, board);
    }
}

void GDisplay::handleValidChessboardClick(int colIndex, int rowIndex, ChessBoard &board) {
    auto clickedPiece = board.getPiece(colIndex, rowIndex);

    if (selectedPiece != nullptr) {
        handleSelectedPieceClick(clickedPiece, colIndex, rowIndex, board);
    } else {
        selectedPiece = clickedPiece;
    }
}

void GDisplay::handleSelectedPieceClick(ChessPiece *clickedPiece, int colIndex, int rowIndex, ChessBoard &board) {
    if (clickedPiece != nullptr) {
        handleMoveToOccupiedSquare(clickedPiece, colIndex, rowIndex, board);
    } else if (selectedPiece->canMoveTo(colIndex, rowIndex, &board)) {
        handleMoveToEmptySquare(colIndex, rowIndex, board);
    } else {
        selectedPiece = nullptr;
    }
}

void GDisplay::handleMoveToOccupiedSquare(ChessPiece *clickedPiece, int colIndex, int rowIndex, ChessBoard &board) {
    if (board.movePiece(selectedPiece->getX(), selectedPiece->getY(), colIndex, rowIndex, isCurrentPlayerWhite)) {
        isCurrentPlayerWhite = !isCurrentPlayerWhite;
        selectedPiece = nullptr;
    } else {
        selectedPiece = clickedPiece;
    }
}

void GDisplay::handleMoveToEmptySquare(int colIndex, int rowIndex, ChessBoard &board) {
    if (board.movePiece(selectedPiece->getX(), selectedPiece->getY(), colIndex, rowIndex, isCurrentPlayerWhite)) {
        isCurrentPlayerWhite = !isCurrentPlayerWhite;
    }
    selectedPiece = nullptr;
}
