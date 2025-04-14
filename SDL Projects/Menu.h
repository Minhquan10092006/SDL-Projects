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
	SDL_Color hoverColor; // màu khi trỏ chuột lên
	bool isHovered; // biến kiểm tra xem chuột có đang chỉ vào rect ko

};

class Menu {
public:
	Menu(SDL_Renderer* renderer);
	~Menu(); // destructor giải phóng tài nguyên

	bool handleEvent(SDL_Event& e);
	void render();
	
	int getSelectedOption(); // lấy lựa chọn hiện tại
	bool loadBackground(const std::string& filePath);

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* background;
	std::vector<Button> buttons;
	int selectedOption;
};
#endif // !MENU_H

