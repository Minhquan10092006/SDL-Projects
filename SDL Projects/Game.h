#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

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
    void createBricks();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Ball* ball;
    Paddle paddle;
    std::vector<Brick> bricks; // khai báo vactor brick (làm vector cho dễ chỉnh sửa)
};

#endif
