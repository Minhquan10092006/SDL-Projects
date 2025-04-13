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

        // Kiểm tra nếu chuột nhấn vào nút trượt
        if (mouseX >= knobRect.x && mouseX <= knobRect.x + knobRect.w &&
            mouseY >= knobRect.y && mouseY <= knobRect.y + knobRect.h) {
            isDragging = true; // Bắt đầu kéo
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        isDragging = false; // Kết thúc kéo
    }
    else if (event.type == SDL_MOUSEMOTION && isDragging) {
        int mouseX = event.motion.x;

        // Giới hạn vị trí của nút trượt trong thanh ngang
        knobRect.x = std::max(x, std::min(mouseX - knobRect.w / 2, x + width - knobRect.w));

        // Cập nhật giá trị hiện tại dựa trên vị trí của nút trượt
        currentValue = minValue + (knobRect.x - x) * (maxValue - minValue) / width;
    }
}

void Slider::render(SDL_Renderer* renderer) {
    // Vẽ thanh ngang (track)
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Màu xám
    SDL_RenderFillRect(renderer, &trackRect);

    // Vẽ nút trượt (knob)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
    SDL_RenderFillRect(renderer, &knobRect);
}

int Slider::getValue() const {
    return currentValue;
}