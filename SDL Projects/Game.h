#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Ball.h"
#include "Paddle.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void processInput();
    void update();
    void render();
    void close();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Ball* ball;  
    Paddle paddle;
};

#endif
