#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Paddle.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void close();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Paddle paddle;

    void processInput();
    void update();
    void render();
};

#endif
