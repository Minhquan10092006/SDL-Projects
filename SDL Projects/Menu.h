#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>

struct Button {
	SDL_Rect rect;
	std::string text;
	SDL_Color normalColor;
	SDL_Color hoverColor;
	bool isHovered;

};

class Menu {
public:
	Menu(SDL_Renderer* renderer);
	~Menu();

	bool handleEvent(SDL_Event& e);
	void render();
	
	int getSelectedOption();
	bool loadBackground(const std::string& filePath);

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* background;
	std::vector<Button> buttons;
	int selectedOption;
};
#endif // !MENU_H

