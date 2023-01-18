#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

#include "engine/level_finder.h"
#include "engine/level_runner.h"
#include "engine/player_context.h"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    window = SDL_CreateWindow("Maze Roamer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 832, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
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