#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Brick.h"

class Ball {
public:
    Ball(int x, int y, int size, float speedX, float speedY, SDL_Renderer* renderer);
    ~Ball();

    void update(std::vector<Brick>& bricks);  // cập nhật vị trí bóng, va chạm với tường, gạch
    void render(SDL_Renderer* renderer);
    void reset();

    SDL_Rect& getRect() { return ballRect; }
    float getSpeedX() const { return speedX; } // truy cập và thay đổi vị trí các giá trị 
    float getSpeedY() const { return speedY; }
    void setSpeedX(float sx) { speedX = sx; }
    void setSpeedY(float sy) { speedY = sy; }
    void bounce(const SDL_Rect& paddleRect); // xử lý bóng khi đập vào paddle 
    bool checkBrickCollision(const Brick& brick); // xử lý bóng khi đập vào gạch
    bool ballLost = false;
    float speedX = 3.0;
    float speedY = -3.0;


private:
    Uint32 lastUpdateTime; // dùng để tính thười gian giữa các khung hình 
    SDL_Rect ballRect;
    
    int lives = 3;
    
    SDL_Texture* ballTexture;
};

#endif