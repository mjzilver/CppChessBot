#include <string>
#include "ChessGame.h"

int main(int argc, char* argv[]) {
    bool useGui = true;

    // Check if "-nogui" is passed as a command line argument
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-nogui") {
            useGui = false;
            break;
        }
    }

    {
        ChessGame game;
        game.startGame(useGui);
    }

    return 0;
}