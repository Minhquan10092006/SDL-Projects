#include "Paddle.h"

Paddle::Paddle() {
    paddleRect = { 350, 550, 100, 20 }; 
    speed = 5;
    movingLeft = false;
    movingRight = false;
}

// Xử lý phím di chuyển paddle
void Paddle::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            movingLeft = true;
            break;
        case SDLK_RIGHT:
            movingRight = true;
            break;
        }
    }
    else if (e.type == SDL_KEYUP) { 
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            movingLeft = false;
            break;
        case SDLK_RIGHT:
            movingRight = false;
            break;
        }
    }
}


void Paddle::update() {
    if (movingLeft) {
        paddleRect.x -= speed;
    }
    if (movingRight) {
        paddleRect.x += speed;
    }

    
    if (paddleRect.x < 0) paddleRect.x = 0;
    if (paddleRect.x + paddleRect.w > 800) paddleRect.x = 800 - paddleRect.w;
}

// Vẽ paddle
void Paddle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleRect);
}
