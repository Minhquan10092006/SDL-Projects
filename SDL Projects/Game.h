#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include <string>
#include <SDL_mixer.h>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Menu.h"
#include "Slider.h"

enum Gamemode { SURVIVAL, TIME_ATTACK };

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
    bool runMenu();
    bool isRunningGame() const { return isRunning; }
    void resetGame();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Ball* ball;
    Paddle* paddle;
    std::vector<Brick> bricks;
    int score;
    TTF_Font* font;

    void increaseScore(int amount);
    void renderScore();
    void gameOver();

    Gamemode gamemode;
    int timeLeft;
    int lives;
    int highScoreSurvival;
    int highScoreTimeAttack;

    Menu* menu;
    Uint32 startTime;
    Uint32 pausedTime;

    void renderTime();
    void timeUp();
    void loadHighScores();
    void saveHighScores();
    bool isWin = false;
    void gameWin();
    bool isGameOver = false;
    bool isPlayingMusic = false;
    bool isPaused = false;
    SDL_Texture* pauseBackground = nullptr;
    SDL_Texture* gameBackground = nullptr;
    SDL_Texture* loadTexture(const std::string& path);
    SDL_Texture* brickTexture = nullptr;

    Mix_Music* backgroundMusic = nullptr;
    Mix_Chunk* brickHitSound = nullptr;
    Mix_Chunk* paddleHitSound = nullptr;
    Mix_Chunk* gameOverSound = nullptr;
    Slider* volumeSlider;
    int volume;
    bool returnToMenu = false;
};

#endif
