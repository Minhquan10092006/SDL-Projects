#ifndef BRICK_H
#define BRICK_H

#include<iostream>
#include <SDL.h>


class Brick {
public:
    SDL_Rect brickRect;
    bool isDestroyed;
    int strength; 

    Brick(int x, int y, int width, int height, int strength );
    ~Brick();
    void hit();
    void render(SDL_Renderer* renderer);
    bool checkCollision(SDL_Rect ballRect);
    SDL_Rect getRect() const { return brickRect; }

};
#endif  