#include "Ball.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>

Ball::Ball(int x, int y, int size, float speedX, float speedY, SDL_Renderer* renderer) {
    ballRect = { x, y, size , size};
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
        SDL_DestroyTexture(ballTexture); // giai phong texture
    }
}

void Ball::update(std::vector<Brick>& bricks) {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastUpdateTime) / 1000.0f; // Cả đoạn này đưa deltaTime vào speedX và speedY 
                                                                // làm cho fgame ko bị nhanh chậm bất thường
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
    // Xử lý bóng va chạm với gạch
    for (auto& brick : bricks) { // kiem tra tung vien gach
        if (!brick.isDestroyed && SDL_HasIntersection(&ballRect, &brick.brickRect)) {

            // Đánh dấu gạch bị phá
            brick.isDestroyed = true;

            // Xác định mép nào va chạm trước và mép trái phải trên dưới bị bóng đè vào bao nhiêu pĩel
            int leftOverlap = (ballRect.x + ballRect.w) - brick.brickRect.x;
            int rightOverlap = (brick.brickRect.x + brick.brickRect.w) - ballRect.x;
            int topOverlap = (ballRect.y + ballRect.h) - brick.brickRect.y;
            int bottomOverlap = (brick.brickRect.y + brick.brickRect.h) - ballRect.y;

            // Tìm phần giao nhỏ nhất để quyết định hướng nảy
            int minOverlap = std::min({ leftOverlap, rightOverlap, topOverlap, bottomOverlap });

            if (minOverlap == leftOverlap) {
                speedX = -fabs(speedX);  // Nảy qua trái
            }
            else if (minOverlap == rightOverlap) {
                speedX = fabs(speedX);  // Nảy qua phải
            }
            else if (minOverlap == topOverlap) {
                speedY = -fabs(speedY);  // Nảy lên trên
            }
            else if (minOverlap == bottomOverlap) {
                speedY = fabs(speedY);  // Nảy xuống dưới
            }

            break;  // Phá xong 1 viên là dừng kiểm tra
        }
    }

    
}

void Ball::render(SDL_Renderer* renderer) {
    if (ballTexture) {
        SDL_RenderCopy(renderer, ballTexture, nullptr, &ballRect);
    }
}


void Ball::bounce(const SDL_Rect& paddleRect) {
    // Đảo hướng Y để bóng nảy lên trên
    speedY = -speedY;

    int paddleCenter = paddleRect.x + paddleRect.w / 2;
    int ballCenter = ballRect.x + ballRect.w / 2;
    // Tính độ lệch của bóng so với tâm paddle  từ -1 đến 1
    float impact = (float)(ballCenter - paddleCenter) / (paddleRect.w / 2.0f);

    // điều chỉnh hướng X dựa trên điểm va chạm
    speedX = impact * 5.0f;  // Tạt bóng theo hướng lệch  

    // Đảm bảo tốc độ ko quá nhỏ
    if (fabs(speedX) < 1.0f) {
        speedX = (speedX < 0) ? -1.0f : 1.0f;
    }
}


void Ball::reset() {
    ballRect.x = 400;
    ballRect.y = 300;
    speedX = ((std::rand() % 5) - 2) * 2.0f; // Giá trị từ -4 đến 4
    speedY = -5.0f; // Van toc doc co dinh
}