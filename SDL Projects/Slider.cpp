#include "Slider.h"

Slider::Slider(int x, int y, int width, int minValue, int maxValue, int defaultValue, SDL_Renderer* renderer)
    : x(x), y(y), width(width), minValue(minValue), maxValue(maxValue), currentValue(defaultValue), renderer(renderer), isDragging(false) {
    trackRect = { x, y, width, 10 };
    knobRect = { x + (defaultValue - minValue) * width / (maxValue - minValue), y - 5, 10, 20 };
}

void Slider::handleEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        if (mouseX >= knobRect.x && mouseX <= knobRect.x + knobRect.w &&
            mouseY >= knobRect.y && mouseY <= knobRect.y + knobRect.h) {
            isDragging = true;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        isDragging = false;
    }
    else if (event.type == SDL_MOUSEMOTION && isDragging) {
        int mouseX = event.motion.x;

        knobRect.x = std::max(x, std::min(mouseX - knobRect.w / 2, x + width - knobRect.w));
        currentValue = minValue + (knobRect.x - x) * (maxValue - minValue) / width;
    }
}

void Slider::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &trackRect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &knobRect);
}

int Slider::getValue() const {
    return currentValue;
}
