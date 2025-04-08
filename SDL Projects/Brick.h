#ifndef BRICK_H
#define BRICK_H

#include<iostream>
#include <SDL.h>
#include <SDL_image.h>

class Brick {
public:
    SDL_Rect brickRect;
    bool isDestroyed;

    Brick(int x, int y, int width, int height);
    ~Brick();
    void render(SDL_Renderer* renderer, SDL_Texture* texture= nullptr);
    bool checkCollision(SDL_Rect ballRect);
    SDL_Rect getRect() const { return brickRect; }

};
#endif  