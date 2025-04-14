#include "Paddle.h"

Paddle::Paddle(SDL_Renderer* renderer) { // Tạo kích thước padfle
    paddleRect = { 350, 550, 100, 20 };
    speed = 5;
    movingLeft = false;
    movingRight = false;
    paddleTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load("assets/image/paddle.png");
    if (!loadedSurface) {
        std::cerr << "Không tải được ảnh paddle! Lỗi: " << IMG_GetError() << std::endl;
    }
    else {
        paddleTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
}
Paddle::~Paddle() {
    if (paddleTexture != nullptr) {
        SDL_DestroyTexture(paddleTexture);
        paddleTexture = nullptr; // dat con tro ve null sau khi destroy tẽture
    }
}

// Xử lý phím di chuyển paddle
void Paddle::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) { // nếu có phím nhấn xuống
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            movingLeft = true;
            break;
        case SDLK_RIGHT:
            movingRight = true;
            break;
        }
    }
    else if (e.type == SDL_KEYUP) { // nếu có phím thả ra
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
        paddleRect.x -= speed;//khi di sang trai thi vi tri tru di gia tri speed
    }
    if (movingRight) {
        paddleRect.x += speed;//khi di sang phai thi vi tri tru di gia tri speed
    }


    if (paddleRect.x < 0) paddleRect.x = 0;
    if (paddleRect.x + paddleRect.w > 800) paddleRect.x = 800 - paddleRect.w;
}

// Vẽ paddle
void Paddle::render(SDL_Renderer* renderer) {
    if (paddleTexture) {
        SDL_RenderCopy(renderer, paddleTexture, nullptr, &paddleRect); //nullptr dung de truyen tat ca texture chu ko cat 1 ti nao
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // neu ko load dcd texture thi load mau trang(cai nay de debug thoi)
        SDL_RenderFillRect(renderer, &paddleRect);
    }
}
void Paddle::reset() {
    paddleRect.x = 350; // Center horizontally
    paddleRect.y = 550; // Near bottom of the screen
    movingLeft = false;
    movingRight = false;
}