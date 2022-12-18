#include <SDL.h>

#include <iostream>

#include "maze.h"

#include <chrono>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    window = SDL_CreateWindow("Maze Roamer | Score: 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 832, 416, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    maze m("level01.txt", renderer, window);

    auto started = std::chrono::high_resolution_clock::now();
    m.initialize();
    auto done = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
    std::cout << duration << std::endl;

    bool is_running = true;
    SDL_Event event;
    std::memset((void *) &event, 0x00, sizeof(SDL_Event));

    while (is_running && m.is_running()) {
        auto frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    m.move_right();
                    break;

                case SDLK_LEFT:
                    m.move_left();
                    break;

                case SDLK_UP:
                    m.move_up();
                    break;

                case SDLK_DOWN:
                    m.move_down();
                    break;
                }

                break;

            default:
                break;
            }
        }

        m.update();
        m.render();

        auto frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < 50)
        {
            SDL_Delay((int)(50 - frameTime));
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}