#include "Paddle.h"

Paddle::Paddle() {
    paddleRect = { 350, 550, 100, 20 }; // Vị trí & kích thước paddle
    speed = 10;
}

// Xử lý phím di chuyển paddle
void Paddle::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            paddleRect.x -= speed;
            break;
        case SDLK_RIGHT:
            paddleRect.x += speed;
            break;
        }
    }
}

// Giới hạn paddle trong màn hình
void Paddle::update() {
    if (paddleRect.x < 0) paddleRect.x = 0;
    if (paddleRect.x > 700) paddleRect.x = 700;
}

// Vẽ paddle
void Paddle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleRect);
}
