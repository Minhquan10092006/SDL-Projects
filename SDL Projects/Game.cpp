#include "Game.h"
#include <iostream>


Game::  Game() : window(nullptr), renderer(nullptr), isRunning(true), ball(nullptr), paddle(nullptr), lives(3), volume(64){}

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
            int y = 35 + row * (brickHeight + 5);// +5 để làm gahcj k bị dính thành cột
            int strength;
            if (row < 2) {
                strength = 3; // Red bricks
            }
            else if (row < 4) {
                strength = 2; // Yellow bricks
            }
            else {
                strength = 1; // Orange bricks
            }
            bricks.emplace_back(x, y, brickWidth, brickHeight, strength);
        }
    }
}
SDL_Texture* Game::loadTexture(const std::string& path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Không thể load ảnh " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Game::timeUp() {
    SDL_Color textColor = { 255, 255, 0 };  // Màu vàng
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Time is Up! Press R to Restart or Q to Quit", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    //Hiển thị điểm số
    std::string scoreText = "Final Score: " + std::to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_Rect textRect = { 200, 250, 400, 50 };  // Time is Up text
    SDL_Rect scoreRect = { 250, 320, 300, 50 }; // Điểm số

    SDL_FreeSurface(surface);
    SDL_FreeSurface(scoreSurface);

    bool waiting = true;
    while (waiting) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                waiting = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    bricks.clear();
                    lives = 3;
                    score = 0;
                    timeLeft = 60;
                    startTime = SDL_GetTicks();
                    createBricks();
                    ball->reset();
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    isRunning = false;
                    waiting = false;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameBackground, nullptr, nullptr);
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);  //Render điểm số
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(scoreTexture);
}

void Game::renderTime() {
    if (gamemode == TIME_ATTACK) {
        SDL_Color textColor = { 255, 255, 0 };  // Màu vàng
        std::string timeText = "Time: " + std::to_string(timeLeft);

        SDL_Surface* timeSurface = TTF_RenderText_Solid(font, timeText.c_str(), textColor);
        SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);

        SDL_Rect timeRect = { 450, 10, 100, 30 }; // Góc trên bên phải

        SDL_FreeSurface(timeSurface);
        SDL_RenderCopy(renderer, timeTexture, nullptr, &timeRect);
        SDL_DestroyTexture(timeTexture);
    }
}

void Game::gameOver() {
    Mix_PlayChannel(-1, gameOverSound, 0);
    SDL_Color textColor = { 255, 0, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over! Press R to Restart or Q to Quit", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    //Hiển thị điểm số
    std::string scoreText = "Final Score: " + std::to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_Rect textRect = { 200, 250, 400, 50 };  // Game Over text
    SDL_Rect scoreRect = { 250, 320, 300, 50 }; // Điểm số

    SDL_FreeSurface(surface);
    SDL_FreeSurface(scoreSurface);

    bool waiting = true;
    while (waiting) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                waiting = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    bricks.clear();
                    lives = 3;
                    score = 0;
                    timeLeft = 60;
                    startTime = SDL_GetTicks();
                    createBricks();
                    ball->reset();
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    isRunning = false;
                    waiting = false;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameBackground, nullptr, nullptr);
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);  //Render điểm số
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(scoreTexture);
}



void Game::increaseScore(int amount) {
    score += amount;
}

void Game::renderScore() {
    static int lastScore = -1;
    static SDL_Texture* scoreTexture = nullptr;
    static int lastLives = -1;
    static SDL_Texture* livesTexture = nullptr;

    if (score != lastScore) {  // chỉ cập nhật lại texture khi điểm số thay đổi
        lastScore = score;

        if (scoreTexture) SDL_DestroyTexture(scoreTexture);

        SDL_Color TextColor = { 255, 255, 255 };
        std::string scoreText = "Score: " + std::to_string(score);

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), TextColor);
        scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_FreeSurface(textSurface);
    }

    if (lives != lastLives) {
        SDL_Color textColor = { 255, 255, 255 };
        lastLives = lives;
        if (livesTexture) SDL_DestroyTexture(livesTexture);
        std::string livesText = "Lives : " + std::to_string(lives);
        SDL_Surface* livesSurface = TTF_RenderText_Solid(font, livesText.c_str(), textColor);
        livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);
        SDL_FreeSurface(livesSurface);
    }

    SDL_Rect textRect = { 10, 10, 100, 30 };
    SDL_Rect livesRect = { 600,10,100,30 };
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &textRect);
    SDL_RenderCopy(renderer, livesTexture, nullptr, &livesRect);
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL không thể khởi tạo! Lỗi! " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
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

    font = TTF_OpenFont("orange juice 2.0.ttf", 24);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    gameBackground = loadTexture("game_background.png");
    if (!gameBackground) {
        std::cerr << "Không thể load ảnh nền game chính!" << std::endl;
    }
    
    pauseBackground = loadTexture("pause_background.png");
    if (!pauseBackground) {
        std::cerr << "Không thể load ảnh nền Pause!" << std::endl;
    }

    menu = new Menu(renderer);
    if (!menu->loadBackground("menu_background.png")) {
        std::cerr << "Không thể load ảnh nền menu!" << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    backgroundMusic = Mix_LoadMUS("background_music.mp3");
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    Mix_PlayMusic(backgroundMusic, -1); 

    // Tải âm thanh hiệu ứng
    brickHitSound = Mix_LoadWAV("brick_hit.wav");
    if (!brickHitSound) {
        std::cerr << "Failed to load brick hit sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    paddleHitSound = Mix_LoadWAV("paddle_hit.wav");
    if (!paddleHitSound) {
        std::cerr << "Failed to load paddle hit sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    } 

    gameOverSound = Mix_LoadWAV("game_over.wav");
    if (!gameOverSound) {
        std::cerr << "Failed to load game over sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    volumeSlider = new Slider(300, 300, 200, 0, 128, volume, renderer); // Thanh trượt nằm giữa màn hình

    bool inMenu= true;
    while (inMenu) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                return false;
            }
            if (menu->handleEvent(event)) {
                int option = menu->getSelectedOption();
                if (option == 0) gamemode = SURVIVAL;
                else if (option == 1) {
                    gamemode = TIME_ATTACK;
                    timeLeft = 60;
                    startTime = SDL_GetTicks();
                    renderTime();
                    renderTime();
                }
                else if (option == 2) isRunning = false;
                inMenu = false;
            }
        }
        menu->render();
    }


    ball = new Ball(400, 300, 20, 5.0f, -5.0f, renderer);
    paddle = new Paddle(renderer);
    createBricks();
    return true;
}

void Game::run() {
    const int FPS = 60;  // giới hạn khung hình thành 60fps 
    const int frameDelay = 1000 / FPS; // dùng để xác định frame per second

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
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isPaused = !isPaused;  // Đảo trạng thái Pause
                }
            }
            if (isPaused) {
                volumeSlider->handleEvent(event);  // Kéo thanh trượt
            }
            if (!isPaused) {
                paddle->handleEvent(event);
            }
        }
        if (isPaused) {
    SDL_Color textColor = { 255, 255, 255 };

    // Vẽ background Pause
    SDL_RenderCopy(renderer, pauseBackground, nullptr, nullptr);

    // Cập nhật âm lượng dựa trên giá trị của thanh trượt
    int volume = volumeSlider->getValue();
    volumeSlider->render(renderer);

    Mix_Volume(-1, volume);       // Cập nhật âm lượng cho hiệu ứng âm thanh
    Mix_VolumeMusic(volume);      // Cập nhật âm lượng cho nhạc nền

    // Vẽ chữ "Paused - Press ESC to Resume"
    SDL_Surface* pauseSurface = TTF_RenderText_Solid(font, "Paused - Press ESC to Resume", textColor);
    SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
    SDL_Rect pauseRect = { 250, 250, 300, 50 };
    SDL_RenderCopy(renderer, pauseTexture, nullptr, &pauseRect);
    SDL_FreeSurface(pauseSurface);
    SDL_DestroyTexture(pauseTexture);

    // 🔊 Vẽ chữ "Volume: x"
    std::string volumeText = "Volume: " + std::to_string(volume);
    SDL_Surface* volumeSurface = TTF_RenderText_Solid(font, volumeText.c_str(), textColor);
    SDL_Texture* volumeTexture = SDL_CreateTextureFromSurface(renderer, volumeSurface);
    SDL_Rect volumeRect = { 300, 270 + 60, 200, 30 };  // Gần bên dưới thanh trượt (giả định y = 330)
    SDL_RenderCopy(renderer, volumeTexture, nullptr, &volumeRect);
    SDL_FreeSurface(volumeSurface);
    SDL_DestroyTexture(volumeTexture);

    SDL_RenderPresent(renderer);
    continue;  // Không update game khi pause
}

        
        //Thêm Time Attack
        if (gamemode == TIME_ATTACK) {
            Uint32 currentTime = SDL_GetTicks();
            timeLeft = 60 - (currentTime - startTime) / 1000;
            if (timeLeft <= 0) {
                timeUp();
                return;  // Kết thúc game ngay khi hết thời gian
            }
            if (lives <= 0) {
                gameOver();
                return;
            }
        }

        // Cập nhật trạng thái game
        ball->update(bricks);
        paddle->update();

        if (SDL_HasIntersection(&ball->getRect(), &paddle->getRect()) && ball->getSpeedY() > 0) {
            ball->bounce(paddle->getRect());
            Mix_PlayChannel(-1, paddleHitSound, 0);
        }

        for (auto it = bricks.begin(); it != bricks.end();) {
            if (ball->checkBrickCollision(*it)) {
                it->hit();
                Mix_PlayChannel(-1, brickHitSound, 0);
                if (it->isDestroyed) {
                    increaseScore(10);
                    it = bricks.erase(it);
                }
                else {
                    ++it;
                }
                break;
            }
            else {
                ++it;
            }
        }

        if (ball->ballLost) {
            lives--;
            ball->ballLost = false; // Reset cờ
            if (lives <= 0) {
                gameOver();
                if (!isRunning) {
                    break;
                }
            }
            else {
                ball->reset();  // Reset bóng nếu vẫn còn mạng
            }
        }

        if (bricks.empty()) {
            ball->speedX *= 1.1f;
            ball->speedY *= 1.1f;
            createBricks();
            ball->reset();
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameBackground, nullptr, nullptr);
        ball->render(renderer);
        paddle->render(renderer);
        for (auto& brick : bricks) {
            brick.render(renderer);
        }

        renderScore();  // Hiển thị điểm số 
        if (gamemode == TIME_ATTACK) renderTime();  // Hiển thị thời gian nếu ở chế độ Time Attack

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
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (pauseBackground) {
        SDL_DestroyTexture(pauseBackground);
        pauseBackground = nullptr;
    }   

    if (gameBackground) {
        SDL_DestroyTexture(gameBackground);
        gameBackground = nullptr;
    }
   
    if (brickTexture) {
        SDL_DestroyTexture(brickTexture);
        brickTexture = nullptr;
    }

    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }

    if (brickHitSound) {
        Mix_FreeChunk(brickHitSound);
        brickHitSound = nullptr;
    }
    if (paddleHitSound) {
        Mix_FreeChunk(paddleHitSound);
        paddleHitSound = nullptr;
    }
    if (gameOverSound) {
        Mix_FreeChunk(gameOverSound);
        gameOverSound = nullptr;
    }
    if (volumeSlider) {
        delete volumeSlider;
        volumeSlider = nullptr;
    }

    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
