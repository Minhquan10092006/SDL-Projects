#include "Game.h"
#include <iostream>

// Khởi tạo game
Game::Game() : window(nullptr), renderer(nullptr), isRunning(true) {}

// Giải phóng tài nguyên
Game::~Game() {
    close();
}

// Hàm khởi tạo SDL
bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL không thể khởi tạo! Lỗi: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Không thể tạo cửa sổ! Lỗi: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Không thể tạo renderer! Lỗi: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// Vòng lặp game chính
void Game::run() {
    while (isRunning) {
        processInput();
        update();
        render();
        SDL_Delay(16); // Giới hạn FPS khoảng 60
    }
}

// Xử lý sự kiện bàn phím
void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        paddle.handleEvent(event);
    }
}

// Cập nhật game
void Game::update() {
    paddle.update();
}

// Vẽ màn hình
void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    paddle.render(renderer);

    SDL_RenderPresent(renderer);
}

// Dọn dẹp tài nguyên
void Game::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
