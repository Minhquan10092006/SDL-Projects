#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Paddle {
public:
    Paddle(SDL_Renderer* renderer);
    ~Paddle();
    SDL_Rect&  getRect() { return paddleRect; }
    void reset();
    void handleEvent(SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);


private:
    SDL_Rect paddleRect;
    int speed;
    bool movingLeft, movingRight;
    SDL_Texture* paddleTexture;
};

#endif

