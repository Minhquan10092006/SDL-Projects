#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle {
public:
    Paddle();
    SDL_Rect&  getRect() { return paddleRect; }
    void handleEvent(SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect paddleRect;
    int speed;
    bool movingLeft, movingRight;
};

#endif

