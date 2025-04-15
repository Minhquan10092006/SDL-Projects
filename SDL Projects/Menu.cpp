#include "Menu.h"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), background(nullptr), selectedOption(-1) {
    font = TTF_OpenFont("assets/font/FeulismiaDemo-MAmEB.ttf", 24);
    if (!font) {
        std::cerr << "Không thể tải font: " << TTF_GetError() << std::endl;
    }

    buttons = {
        {{300, 200, 200, 50}, "Survival Mode", {255,255,255}, {255,0,0}},
        {{300, 270, 200 ,50}, "Time Attack", {255,255,255}, {255,0,0}},
        {{300, 340, 200 ,50}, "Quit", {255,255,255}, {255,0,0}},
    };
}

Menu::~Menu() {
    if (background) {
        SDL_DestroyTexture(background);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}

bool Menu::loadBackground(const std::string& filePath) {
    SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
    if (!loadedSurface) {
        std::cerr << "Không thể load ảnh nền: " << IMG_GetError() << std::endl;
        return false;
    }

    background = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return background != nullptr;
}

bool Menu::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEMOTION) {
        int mouseX = e.motion.x;
        int mouseY = e.motion.y;

        for (size_t i = 0; i < buttons.size(); i++) {
            if (mouseX >= buttons[i].rect.x && mouseX <= buttons[i].rect.x + buttons[i].rect.w &&
                mouseY >= buttons[i].rect.y && mouseY <= buttons[i].rect.y + buttons[i].rect.h) {
                buttons[i].isHovered = true;
            }
            else {
                buttons[i].isHovered = false;
            }
        }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        for (size_t i = 0; i < buttons.size(); i++) {
            if (mouseX >= buttons[i].rect.x && mouseX <= buttons[i].rect.x + buttons[i].rect.w &&
                mouseY >= buttons[i].rect.y && mouseY <= buttons[i].rect.y + buttons[i].rect.h) {
                selectedOption = i;
                if (buttons[i].text == "Quit") {
                    SDL_Quit();
                    exit(0);
                }
                return true;
            }
        }
    }
    return false;
}

void Menu::render() {
    if (background) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    SDL_Color shadowColor = { 50, 50, 50 };
    SDL_Color titleColor = { 255, 255, 0 };

    TTF_Font* titleFont = TTF_OpenFont("assets/font/FeulismiaDemo-MAmEB.ttf", 48);

    if (titleFont) {
        SDL_Surface* shadowSurface = TTF_RenderText_Solid(titleFont, "Brick Breaker", shadowColor);
        SDL_Texture* shadowTexture = SDL_CreateTextureFromSurface(renderer, shadowSurface);
        SDL_Rect shadowRect = {
            (800 - shadowSurface->w) / 2 + 2,
            80 + 2,
            shadowSurface->w,
            shadowSurface->h
        };

        SDL_Surface* titleSurface = TTF_RenderText_Solid(titleFont, "Brick Breaker", titleColor);
        SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_Rect titleRect = {
            (800 - titleSurface->w) / 2,
            80,
            titleSurface->w,
            titleSurface->h
        };

        SDL_RenderCopy(renderer, shadowTexture, nullptr, &shadowRect);
        SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);

        SDL_FreeSurface(shadowSurface);
        SDL_DestroyTexture(shadowTexture);
        SDL_FreeSurface(titleSurface);
        SDL_DestroyTexture(titleTexture);
        TTF_CloseFont(titleFont);
    }
    else {
        std::cerr << "Không thể tải font lớn cho tiêu đề: " << TTF_GetError() << std::endl;
    }

    for (const auto& button : buttons) {
        SDL_Color color = button.isHovered ? button.hoverColor : button.normalColor;
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, button.text.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_RenderCopy(renderer, textTexture, nullptr, &button.rect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

int Menu::getSelectedOption() {
    return selectedOption;
}
