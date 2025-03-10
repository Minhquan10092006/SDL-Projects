#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <SDL_image.h>

class Ball {
public:
    Ball(int x, int y, int size, float speedX, float speedY, SDL_Renderer* renderer);
    ~Ball();

    void update();
    void render(SDL_Renderer* renderer);
    void reset();

    SDL_Rect& getRect() { return ballRect; }
    float getSpeedX() const { return speedX; }
    float getSpeedY() const { return speedY; }
    void setSpeedX(float sx) { speedX = sx; }
    void setSpeedY(float sy) { speedY = sy; }
    void bounce(const SDL_Rect& paddleRect);


private:
    Uint32 lastUpdateTime;
    SDL_Rect ballRect;
    float speedX=3.0;
    float speedY = -3.0;
    SDL_Texture* ballTexture; 
};

#endif
