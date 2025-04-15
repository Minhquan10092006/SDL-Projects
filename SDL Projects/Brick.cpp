#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, int strength) {
    brickRect = { x, y, width, height };
    this->strength = strength;
    isDestroyed = false;
}

Brick::~Brick() {}

void Brick::render(SDL_Renderer* renderer) {
    if (strength == 1) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    }
    else if (strength == 2) {
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    }
    else if (strength == 3) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &brickRect);
}

void Brick::hit() {
    if (strength > 0) {
        strength--;
        if (strength <= 0) {
            isDestroyed = true;
        }
    }
}

bool Brick::checkCollision(SDL_Rect ballRect) {
    return SDL_HasIntersection(&brickRect, &ballRect);
}
