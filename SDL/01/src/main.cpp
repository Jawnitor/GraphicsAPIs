#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to init SDL: %s", SDL_GetError());
        return 1;
    }
    std::cout << "SDL init"
              << "\n";

    SDL_Quit();
    return 0;
}
