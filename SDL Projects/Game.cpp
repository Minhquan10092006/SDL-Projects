#include "Game.h"
#include <iostream>



Game::Game() : window(nullptr), renderer(nullptr), isRunning(true), ball(nullptr) {}


Game::~Game() {
    close();
}
void Game::createBricks() {
    int brickWidth = 60;
    int brickHeight = 20;
    int rows = 5;
    int cols = 10;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int x = 60 + col * (brickWidth + 5);// +5 để làm cách viên gạch cách đều nhau ko bị dính thành hàng
            int y = 20 + row * (brickHeight + 5);// +5 để làm gahcj k bị dính thành cột
            bricks.emplace_back(Brick(x, y, brickWidth, brickHeight));
        }
    }
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL không thể khởi tạo! Lỗi! " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Không thể tạo cửa sổ! Lỗi! " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Không thể tạo renderer! Lỗi! " << SDL_GetError() << std::endl;
        return false;
    }


    ball = new Ball(400, 300, 20, 5.0f, -5.0f, renderer);
    createBricks();
    return true;
}

void Game::run() {
    const int FPS = 60;  // giới hạn khung hình thành 60fps 
    const int frameDelay = 1000 / FPS; // dùng để xác định frame pẻ second

    Uint32 frameStart;
    int frameTime;

    while (isRunning) {
        frameStart = SDL_GetTicks();
        // xử lý sự kiện
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            paddle.handleEvent(event);
        }

        // Cập nhật trạng thái game
        ball->update(bricks);
        paddle.update();

        if (SDL_HasIntersection(&ball->getRect(), &paddle.getRect()) && ball->getSpeedY() > 0) {
            ball->bounce(paddle.getRect());
        }



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        ball->render(renderer);
        paddle.render(renderer);
        for (auto& brick : bricks) {
            brick.render(renderer); // render từng viên gahcj ra 
        }

        SDL_RenderPresent(renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime); // Đảm bảo game ko bị delay và nhận chính xác frame per second
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
