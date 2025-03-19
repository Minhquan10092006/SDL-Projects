#include "Brick.h"

Brick::Brick(int x, int y, int width, int height) {
    brickRect = { x, y, width, height };
    isDestroyed = false;
}

Brick::~Brick() {}

void Brick::render(SDL_Renderer* renderer) {
    if (!isDestroyed) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Màu đỏ
        SDL_RenderFillRect(renderer, &brickRect);
    }
}

bool Brick::checkCollision(SDL_Rect ballRect) {
    if (SDL_HasIntersection(&brickRect, &ballRect)) {
        isDestroyed = true;
        return true;
    }
    return false;
}