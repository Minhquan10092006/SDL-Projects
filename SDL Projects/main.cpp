#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    Mix_Music* bgm = Mix_LoadMUS("background.mp3");
    if (!bgm) {
        std::cerr << "Failed to load music! Mix_Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    Mix_PlayMusic(bgm, -1);
    std::cout << "Playing music... Press Enter to quit." << std::endl;
    std::cin.get();

    Mix_FreeMusic(bgm);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

