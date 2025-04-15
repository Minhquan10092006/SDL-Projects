#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init()) {
        std::cerr << "Failed to initialize the game.\n";
        return -1;
    }

    while (game.isRunningGame()) {
        if (game.runMenu()) {
            game.run();
        }
    }

    game.close();
    return 0;
}
