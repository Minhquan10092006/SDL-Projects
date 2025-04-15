#include "Ball.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Ball::Ball(int x, int y, int size, float speedX, float speedY, SDL_Renderer* renderer) {
    ballRect = { x, y, size , size };
    this->speedX = speedX;
    this->speedY = speedY;
    std::srand(std::time(nullptr));

    SDL_Surface* surface = IMG_Load("assets/image/ball.png");
    if (!surface) {
        std::cerr << "Không thể load hình ảnh bóng! Lỗi: " << IMG_GetError() << std::endl;
        ballTexture = nullptr;
    }
    else {
        ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

Ball::~Ball() {
    if (ballTexture) {
        SDL_DestroyTexture(ballTexture);
    }
}

void Ball::update(std::vector<Brick>& bricks) {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastUpdateTime) / 1000.0f;
    lastUpdateTime = currentTime;

    ballRect.x += static_cast<int>(speedX);
    ballRect.y += static_cast<int>(speedY);

    if (ballRect.x <= 0 || ballRect.x + ballRect.w >= 800) {
        speedX = -speedX;
    }
    if (ballRect.y <= 0) {
        speedY = -speedY;
    }
    if (ballRect.y > 600) {
        ballLost = true;
        lives--;
        reset();
    }

    for (auto& brick : bricks) {
        if (!brick.isDestroyed && SDL_HasIntersection(&ballRect, &brick.brickRect)) {
            int leftOverlap = (ballRect.x + ballRect.w) - brick.brickRect.x;
            int rightOverlap = (brick.brickRect.x + brick.brickRect.w) - ballRect.x;
            int topOverlap = (ballRect.y + ballRect.h) - brick.brickRect.y;
            int bottomOverlap = (brick.brickRect.y + brick.brickRect.h) - ballRect.y;

            int minOverlap = std::min({ leftOverlap, rightOverlap, topOverlap, bottomOverlap });

            if (minOverlap == topOverlap && speedY > 0) {
                speedY = -fabs(speedY);
            }
            else if (minOverlap == bottomOverlap && speedY < 0) {
                speedY = fabs(speedY);
            }
            else if (minOverlap == leftOverlap && speedX > 0) {
                speedX = -fabs(speedX);
            }
            else if (minOverlap == rightOverlap && speedX < 0) {
                speedX = fabs(speedX);
            }

            break;
        }
    }
}

bool Ball::checkBrickCollision(const Brick& brick) {
    int ballCenterX = ballRect.x + ballRect.w / 2;
    int ballCenterY = ballRect.y + ballRect.h / 2;

    int brickCenterX = brick.brickRect.x + brick.brickRect.w / 2;
    int brickCenterY = brick.brickRect.y + brick.brickRect.h / 2;

    int dx = abs(ballCenterX - brickCenterX);
    int dy = abs(ballCenterY - brickCenterY);

    int ballRadius = ballRect.w / 2;

    if (dx < (brick.brickRect.w / 2 + ballRadius) && dy < (brick.brickRect.h / 2 + ballRadius)) {
        return true;
    }
    return false;
}

void Ball::render(SDL_Renderer* renderer) {
    if (ballTexture) {
        SDL_RenderCopy(renderer, ballTexture, nullptr, &ballRect);
    }
}

void Ball::bounce(const SDL_Rect& paddleRect) {
    speedY = -speedY;

    int paddleCenter = paddleRect.x + paddleRect.w / 2;
    int ballCenter = ballRect.x + ballRect.w / 2;

    float impact = (float)(ballCenter - paddleCenter) / (paddleRect.w / 2.0f);

    speedX = impact * 5.0f;

    if (fabs(speedX) < 1.0f) {
        speedX = (speedX < 0) ? -1.5f : 1.5f;
    }

    if (fabs(speedX) > fabs(speedY) * 2.5f) {
        speedX = (speedX < 0) ? -fabs(speedY) * 2.5f : fabs(speedY) * 2.5f;
    }
}

void Ball::reset() {
    ballRect.x = 400;
    ballRect.y = 300;
    speedX = ((std::rand() % 5) - 2) * 2.0f;
    speedY = -5.0f;
}
