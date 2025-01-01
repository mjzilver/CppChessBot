#include <string>

#include "AI/AI.h"
#include "Chess/ChessBoard.h"
#include "UI/ConsoleDisplay.h"
#include "UI/GDisplay.h"
#include "UI/IDisplay.h"

int main(int argc, char* argv[]) {
    bool useGui = true;

    // Check if "-nogui" is passed as a command line argument
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-nogui") {
            useGui = false;
            break;
        }
    }

    AI ai(5);
    IDisplay* display = nullptr;
    ChessBoard board;

    if (useGui) {
        display = new GDisplay(&ai);
    } else {
        display = new ConsoleDisplay();
    }

    display->drawLoop(board);

    delete display;

    return 0;
}