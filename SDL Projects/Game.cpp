#include "Game.h"
#include "Ball.h"
#include <iostream>



Game::Game() : window(nullptr), renderer(nullptr), isRunning(true), ball(nullptr) {}


Game::~Game() {
    close();
}

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

    
    ball = new Ball(400, 300, 20, 5.0f, -5.0f, renderer);
    return true;
}

void Game::run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (isRunning) {
        frameStart = SDL_GetTicks();
        // Xử lý sự kiện
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            paddle.handleEvent(event);
        }

        // Cập nhật trạng thái game
        ball->update();
        paddle.update();

        if (SDL_HasIntersection(&ball->getRect(), &paddle.getRect()) && ball->getSpeedY() > 0) {
            ball->bounce(paddle.getRect());
        }


        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        ball->render(renderer); 
        paddle.render(renderer);

        SDL_RenderPresent(renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}



void Game::close() {
    if (ball) {
        delete ball;
        ball = nullptr;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

