#ifndef BRICK_H
#define BRICK_H

#include <SDL.h>

class Brick {
public:
    SDL_Rect brickRect;
    bool isDestroyed;

    Brick(int x, int y, int width, int height);
    ~Brick();
    void render(SDL_Renderer* renderer);
    bool checkCollision(SDL_Rect ballRect);
};
#endif