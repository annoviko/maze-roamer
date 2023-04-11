#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

#include "engine/level_finder.h"
#include "engine/level_runner.h"
#include "engine/player_context.h"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_DisplayMode desktop_mode;
    if (SDL_GetDesktopDisplayMode(0, &desktop_mode) != 0) {
        std::cout << "Unable to get desktop display mode: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window;
    window = SDL_CreateWindow("Maze Roamer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, desktop_mode.w, desktop_mode.h, SDL_WINDOW_FULLSCREEN);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (TTF_Init() < 0) {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }

    level_finder finder(".");
    player_context::ptr context = std::make_shared<player_context>();

    level_runner runner(renderer, context);
    for (std::size_t i = 0; (i < finder.get_levels().size()) && !runner.is_game_over(); i++) {
        runner.run(finder.get_levels()[i]);
    }

    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}