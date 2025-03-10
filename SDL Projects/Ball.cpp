#include "Ball.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>

Ball::Ball(int x, int y, int size, float speedX, float speedY, SDL_Renderer* renderer) {
    ballRect = { x, y, size, size };
    this->speedX = speedX;
    this->speedY = speedY;
    std::srand(std::time(nullptr)); // Khởi tạo seed ngẫu nhiên

    // Load hình ảnh bóng
    SDL_Surface* surface = IMG_Load("ball.png");
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

void Ball::update() {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastUpdateTime) / 1000.0f;
    lastUpdateTime = currentTime;
    ballRect.x += static_cast<int>(speedX);
    ballRect.y += static_cast<int>(speedY);

    // Xử lý va chạm với tường
    if (ballRect.x <= 0 || ballRect.x + ballRect.w >= 800) {
        speedX = -speedX;
    }
    if (ballRect.y <= 0) {
        speedY = -speedY;
    }
    if (ballRect.y > 600) {
        reset();
    }
}

void Ball::render(SDL_Renderer* renderer) {
    if (ballTexture) {
        SDL_RenderCopy(renderer, ballTexture, nullptr, &ballRect);
    }
}

void Ball::bounce(const SDL_Rect& paddleRect) {
    // Đảo ngược hướng Y để bóng nảy lên
    speedY = -speedY;

    // Xác định vị trí va chạm của bóng so với tâm thanh chắn
    int paddleCenter = paddleRect.x + paddleRect.w / 2;
    int ballCenter = ballRect.x + ballRect.w / 2;
    float impact = (float)(ballCenter - paddleCenter) / (paddleRect.w / 2.0f);

    // Điều chỉnh hướng X dựa trên điểm va chạm, để tạo quỹ đạo hình chữ V
    speedX = impact * 5.0f;

    // Đảm bảo speedX không quá nhỏ để tránh bóng đi thẳng lên xuống
    if (abs(speedX) < 1.0f) {
        speedX = (speedX < 0) ? -1.0f : 1.0f;
    }
}

void Ball::reset() {
    ballRect.x = 400;
    ballRect.y = 300;
    speedX = ((std::rand() % 5) - 2) * 2.0f; // Giá trị từ -4.0 đến 4.0
    speedY = -5.0f; // Vận tốc dọc cố định
}
