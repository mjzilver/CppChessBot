#include "ConsoleDisplay.h"

#include <iostream>
#include <thread>

#include "../Chess/PieceType.h"

void ConsoleDisplay::drawBoard(const ChessBoard &board) {
    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << ' ';
        for (int j = 0; j < 8; ++j) {
            PieceType piece = board.getPieceTypeAt(j, i);
            bool isWhite = board.isPieceAt(j, i, true);
            if (piece == -1) {
                // No piece at this location
                std::cout << ' ';
            } else {
                switch (piece) {
                    case PAWN:
                        std::cout << (isWhite ? 'P' : 'p');
                        break;
                    case ROOK:
                        std::cout << (isWhite ? 'R' : 'r');
                        break;
                    case KNIGHT:
                        std::cout << (isWhite ? 'N' : 'n');
                        break;
                    case BISHOP:
                        std::cout << (isWhite ? 'B' : 'b');
                        break;
                    case QUEEN:
                        std::cout << (isWhite ? 'Q' : 'q');
                        break;
                    case KING:
                        std::cout << (isWhite ? 'K' : 'k');
                        break;
                    default:
                        break;
                }
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

std::string ConsoleDisplay::receiveInput() {
    std::string input;
    std::cin >> input;
    return input;
}

void ConsoleDisplay::drawLoop(ChessBoard &board) {
    while (true) {
        handleInput(board);

        static bool isAIThreadRunning = false;
        if (!isCurrentPlayerWhite && !isAIThreadRunning) {
            isAIThreadRunning = true;
            std::thread aiThread([&]() {
                ai->makeMove(&board, false);
                isCurrentPlayerWhite = true;
                isAIThreadRunning = false;
                drawBoard(board);
            });

            aiThread.detach();
        }
    }

    std::cout << "Game over!" << std::endl;
}

bool ConsoleDisplay::makeMove(ChessBoard &board, const std::string &moveInput) {
    if ((moveInput.size() < 4 || moveInput.size() > 5) || !isalpha(moveInput[0]) || !isdigit(moveInput[1]) ||
        !isalpha(moveInput[2]) || !isdigit(moveInput[3])) {
        std::cout << "Invalid move format. Please use the format 'a2a4'." << std::endl;
        return false;
    }

    // Convert input to coordinates
    int fromX = tolower(moveInput[0]) - 'a';
    int fromY = '8' - moveInput[1];
    int toX = tolower(moveInput[2]) - 'a';
    int toY = '8' - moveInput[3];

    if (board.movePiece(fromX, fromY, toX, toY)) {
        return true;
    } else {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }
}

void ConsoleDisplay::handleInput(ChessBoard &board) {
    drawBoard(board);
    std::cout << "Player 1's turn (white): " << std::endl;
    std::string moveInputPlayer1 = receiveInput();
    while (!makeMove(board, moveInputPlayer1)) {
        moveInputPlayer1 = receiveInput();
        drawBoard(board);
    }
    isCurrentPlayerWhite = false;
    drawBoard(board);
}
