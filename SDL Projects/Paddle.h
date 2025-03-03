#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle {
public:
    Paddle();

    void handleEvent(SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect paddleRect;
    int speed;
};

#endif
#pragma once
