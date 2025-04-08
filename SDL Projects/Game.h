#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Menu.h"

enum Gamemode {SURVIVAL, TIME_ATTACK};

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void processInput();
    void update();
    void render();
    void close();
    void createBricks();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Ball* ball;
    Paddle* paddle;
    std::vector<Brick> bricks; // khai báo vactor brick (làm vector cho dễ chỉnh sửa)
    int score;
    TTF_Font* font;

    void increaseScore(int amount);
    void renderScore();
    void gameOver();
    
    Gamemode gamemode;
    int timeLeft;
    int lives;
    float SpeedMultipiar;

    Menu* menu;
    Uint32 startTime;

    void renderTime();
    void timeUp();
    bool isPaused = false;
    SDL_Texture* pauseBackground = nullptr;
    SDL_Texture* gameBackground = nullptr;
    SDL_Texture* loadTexture(const std::string& path);
    SDL_Texture* brickTexture = nullptr;
    
};

#endif
