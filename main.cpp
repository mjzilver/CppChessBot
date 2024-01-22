#include "ChessGame.h"

#include <string>

int main(int argc, char* argv[]) {
    bool useGui = false;

    // Check if "-gui" is passed as a command line argument
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-gui") {
            useGui = true;
            break;
        }
    }

    ChessGame game;
    game.startGame(useGui);

    return 0;
}