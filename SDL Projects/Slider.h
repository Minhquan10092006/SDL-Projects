#ifndef SLIDER_H
#define SLIDER_H

#include <SDL.h>
#include <algorithm>

class Slider {
public:
    Slider(int x, int y, int width, int minValue, int maxValue, int defaultValue, SDL_Renderer* renderer);
    void handleEvent(SDL_Event& event);
    void render(SDL_Renderer* renderer);
    int getValue() const;

private:
    int x, y, width;
    int minValue, maxValue, currentValue;
    bool isDragging;
    SDL_Rect trackRect, knobRect;
    SDL_Renderer* renderer; // Thêm thành viên renderer
};

#endif