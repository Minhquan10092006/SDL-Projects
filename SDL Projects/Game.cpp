#include "Game.h"
#include <iostream>


Game::Game() : window(nullptr), renderer(nullptr), isRunning(true), ball(nullptr), paddle(nullptr), lives(3), volume(64), returnToMenu(false) {}

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
            int x = 60 + col * (brickWidth + 5);
            int y = 35 + row * (brickHeight + 5);
            int strength;
            if (row < 2) {
                strength = 3;
            }
            else if (row < 4) {
                strength = 2;
            }
            else {
                strength = 1;
            }
            bricks.emplace_back(x, y, brickWidth, brickHeight, strength);
        }
    }
}

void Game::resetGame() {
    if (!isPlayingMusic) {
        Mix_PlayMusic(backgroundMusic, -1);
        isPlayingMusic = true;
    }
    bricks.clear();
    score = 0;
    lives = 3;
    timeLeft = 120;
    startTime = SDL_GetTicks();
    createBricks();
    if (ball) {
        ball->reset();
    }
    if (paddle) {
        paddle->reset();
    }
    isGameOver = false;
    isWin = false;
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

void Game::loadHighScores() {
    std::ifstream file("highscores.txt");
    if (file.is_open()) {
        file >> highScoreSurvival >> highScoreTimeAttack;
        file.close();
    }
    else {
        highScoreSurvival = 0;
        highScoreTimeAttack = 0;
    }
}

void Game::saveHighScores() {
    std::ofstream file("highscores.txt");
    if (file.is_open()) {
        file << highScoreSurvival << " " << highScoreTimeAttack;
        file.close();
    }
}

void Game::gameWin() {
    if (score > highScoreTimeAttack) {
        highScoreTimeAttack = score;
        saveHighScores();
    }

    SDL_Color textColor = { 0, 255, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "You Win! Press R to Restart, Q to Quit, or M to Menu", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    std::string scoreText = "Final Score: " + std::to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    std::string highScoreText = "High Score (Time Attack): " + std::to_string(highScoreTimeAttack);
    SDL_Surface* highScoreSurface = TTF_RenderText_Solid(font, highScoreText.c_str(), textColor);
    SDL_Texture* highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);

    SDL_Rect textRect = { 150, 250, 500, 50 };
    SDL_Rect scoreRect = { 250, 320, 300, 50 };
    SDL_Rect highScoreRect = { 250, 390, 300, 50 };

    SDL_FreeSurface(surface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(highScoreSurface);

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
                    resetGame();
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    isRunning = false;
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_m) {
                    returnToMenu = true;
                    resetGame();
                    waiting = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameBackground, nullptr, nullptr);
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
        SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(highScoreTexture);
}

bool Game::runMenu() {
    bool inMenu = true;

    if (!isPlayingMusic && backgroundMusic) {
        Mix_PlayMusic(backgroundMusic, -1);
        isPlayingMusic = true;
    }
    while (inMenu) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                return false;
            }
            if (menu->handleEvent(event)) {
                int option = menu->getSelectedOption();
                if (option == 0) {
                    gamemode = SURVIVAL;
                    resetGame();
                }
                else if (option == 1) {
                    gamemode = TIME_ATTACK;
                    timeLeft = 120;
                    startTime = SDL_GetTicks();
                    resetGame();
                }
                else if (option == 2) {
                    isRunning = false;
                    return false;
                }
                inMenu = false;
            }

        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        menu->render();
        SDL_RenderPresent(renderer);
    }
    return true;
}

void Game::timeUp() {
    if (score > highScoreTimeAttack) {
        highScoreTimeAttack = score;
        saveHighScores();
    }
    if (!isGameOver) {
        isGameOver = true;
        if (Mix_PlayingMusic()) {
            Mix_HaltMusic();
        }
        isPlayingMusic = false;
        Mix_PlayChannel(-1, gameOverSound, 0);
    }
    SDL_Color textColor = { 255, 255, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Time is Up! Press R to Restart, Q to Quit, or M to Menu", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    std::string scoreText = "Final Score: " + std::to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    std::string highScoreText = "High Score (Time Attack): " + std::to_string(highScoreTimeAttack);
    SDL_Surface* highScoreSurface = TTF_RenderText_Solid(font, highScoreText.c_str(), textColor);
    SDL_Texture* highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);

    SDL_Rect textRect = { 150, 250, 500, 50 };
    SDL_Rect scoreRect = { 250, 320, 300, 50 };
    SDL_Rect highScoreRect = { 250, 390, 300, 50 };

    SDL_FreeSurface(surface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(highScoreSurface);

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
                    resetGame();
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    isRunning = false;
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_m) {
                    returnToMenu = true;
                    resetGame();
                    waiting = false;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameBackground, nullptr, nullptr);
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
        SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(highScoreTexture);
}

void Game::renderTime() {
    if (gamemode == TIME_ATTACK) {
        SDL_Color textColor = { 255, 255, 0 };
        std::string timeText = "Time: " + std::to_string(timeLeft);

        SDL_Surface* timeSurface = TTF_RenderText_Solid(font, timeText.c_str(), textColor);
        SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);

        SDL_Rect timeRect = { 450, 10, 100, 30 };

        SDL_FreeSurface(timeSurface);
        SDL_RenderCopy(renderer, timeTexture, nullptr, &timeRect);
        SDL_DestroyTexture(timeTexture);
    }
}

void Game::gameOver() {
    if (gamemode == SURVIVAL && score > highScoreSurvival) {
        highScoreSurvival = score;
        saveHighScores();
    }
    else if (gamemode == TIME_ATTACK && score > highScoreTimeAttack) {
        highScoreTimeAttack = score;
        saveHighScores();
    }
    if (!isGameOver) {
        isGameOver = true;

        if (Mix_PlayingMusic()) {
            Mix_HaltMusic();
        }
        isPlayingMusic = false;
        Mix_PlayChannel(-1, gameOverSound, 0);
    }
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over! Press R to Restart, Q to Quit, or M to Menu", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    std::string scoreText = "Final Score: " + std::to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    std::string highScoreText;
    if (gamemode == SURVIVAL) {
        highScoreText = "High Score (Survival): " + std::to_string(highScoreSurvival);
    }
    else if (gamemode == TIME_ATTACK) {
        highScoreText = "High Score (Time Attack): " + std::to_string(highScoreTimeAttack);
    }
    SDL_Surface* highScoreSurface = TTF_RenderText_Solid(font, highScoreText.c_str(), textColor);
    SDL_Texture* highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);

    SDL_Rect textRect = { 150, 250, 500, 50 };
    SDL_Rect scoreRect = { 250, 320, 300, 50 };
    SDL_Rect highScoreRect = { 250, 390, 300, 50 };

    SDL_FreeSurface(surface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(highScoreSurface);

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
                    resetGame();
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    isRunning = false;
                    waiting = false;
                }
                if (event.key.keysym.sym == SDLK_m) {
                    returnToMenu = true;
                    resetGame();
                    waiting = false;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameBackground, nullptr, nullptr);
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
        SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(highScoreTexture);
}

void Game::increaseScore(int amount) {
    score += amount;
}

void Game::renderScore() {
    static int lastScore = -1;
    static SDL_Texture* scoreTexture = nullptr;
    static int lastLives = -1;
    static SDL_Texture* livesTexture = nullptr;

    if (score != lastScore) {
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

    font = TTF_OpenFont("assets/font/MelonCamp-4nMxY.ttf", 24);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    gameBackground = loadTexture("assets/image/game_background.png");
    if (!gameBackground) {
        std::cerr << "Không thể load ảnh nền game chính!" << std::endl;
    }

    pauseBackground = loadTexture("assets/image/pause_background.png");
    if (!pauseBackground) {
        std::cerr << "Không thể load ảnh nền Pause!" << std::endl;
    }

    menu = new Menu(renderer);
    if (!menu->loadBackground("assets/image/menu_background.png")) {
        std::cerr << "Không thể load ảnh nền menu!" << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    backgroundMusic = Mix_LoadMUS("assets/sound/background_music.mp3");
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    Mix_PlayMusic(backgroundMusic, -1);

    brickHitSound = Mix_LoadWAV("assets/sound/brick_hit.wav");
    if (!brickHitSound) {
        std::cerr << "Failed to load brick hit sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    paddleHitSound = Mix_LoadWAV("assets/sound/paddle_hit.wav");
    if (!paddleHitSound) {
        std::cerr << "Failed to load paddle hit sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    gameOverSound = Mix_LoadWAV("assets/sound/game_over.wav");
    if (!gameOverSound) {
        std::cerr << "Failed to load game over sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    loadHighScores();

    volumeSlider = new Slider(300, 300, 200, 0, 128, volume, renderer);

    if (!runMenu()) {
        return false;
    }

    ball = new Ball(400, 300, 20, 5.0f, -5.0f, renderer);
    paddle = new Paddle(renderer);
    createBricks();
    return true;
}

void Game::run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    returnToMenu = false;

    while (isRunning && !returnToMenu) {
        frameStart = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isPaused = !isPaused;
                    if (isPaused) {
                        pausedTime = SDL_GetTicks();
                    }
                    else {
                        startTime += SDL_GetTicks() - pausedTime;
                    }
                }
            }
            if (isPaused) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_m) {
                        returnToMenu = true;
                        isPaused = false;
                    }
                }
                volumeSlider->handleEvent(event);
            }
            if (!isPaused) {
                paddle->handleEvent(event);
            }
        }
        if (isPaused) {
            SDL_Color textColor = { 0, 0, 0 };
            SDL_RenderCopy(renderer, pauseBackground, nullptr, nullptr);
            int volume = volumeSlider->getValue();
            volumeSlider->render(renderer);
            Mix_Volume(-1, volume);
            Mix_VolumeMusic(volume);
            SDL_Surface* pauseSurface = TTF_RenderText_Solid(font, "Paused - Press ESC to Resume, M to Menu", textColor);
            SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
            SDL_Rect pauseRect = { 200, 250, 400, 50 };
            SDL_RenderCopy(renderer, pauseTexture, nullptr, &pauseRect);
            SDL_FreeSurface(pauseSurface);
            SDL_DestroyTexture(pauseTexture);
            std::string volumeText = "Volume: " + std::to_string(volume);
            SDL_Surface* volumeSurface = TTF_RenderText_Solid(font, volumeText.c_str(), textColor);
            SDL_Texture* volumeTexture = SDL_CreateTextureFromSurface(renderer, volumeSurface);
            SDL_Rect volumeRect = { 300, 270 + 60, 200, 30 };
            SDL_RenderCopy(renderer, volumeTexture, nullptr, &volumeRect);
            SDL_FreeSurface(volumeSurface);
            SDL_DestroyTexture(volumeTexture);
            SDL_RenderPresent(renderer);
            continue;
        }

        if (gamemode == TIME_ATTACK && !isPaused) {
            Uint32 currentTime = SDL_GetTicks();
            timeLeft = 120 - (currentTime - startTime) / 1000;
            if (timeLeft <= 0) {
                timeUp();
                return;
            }
            if (lives <= 0) {
                gameOver();
                return;
            }
            if (isWin) {
                gameWin();
                return;
            }
        }

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
            ball->ballLost = false;
            if (lives <= 0) {
                gameOver();
                if (!isRunning) {
                    break;
                }
            }
            else {
                ball->reset();
            }
        }

        if (bricks.empty()) {
            if (gamemode == TIME_ATTACK) {
                isWin = true;
                break;
            }
            else {
                ball->speedX *= 1.1f;
                ball->speedY *= 1.1f;
                createBricks();
                ball->reset();
            };
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameBackground, nullptr, nullptr);
        ball->render(renderer);
        paddle->render(renderer);
        for (auto& brick : bricks) {
            brick.render(renderer);
        }

        renderScore();
        if (gamemode == TIME_ATTACK) renderTime();

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