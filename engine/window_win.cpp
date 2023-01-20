#include "window_win.h"


#include <exception>
#include <string>

#include <SDL_ttf.h>


window_win::window_win() {
    m_window = SDL_CreateWindow("Congratulations!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN);
    if (!m_window) {
        throw std::exception("impossible to create SDL window");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect rect = { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT };
    SDL_SetRenderDrawColor(m_renderer, 0xff, 0x5b, 0x00, 0xff);
    SDL_RenderFillRect(m_renderer, &rect);

    TTF_Font* font = TTF_OpenFont("fonts/Symtext.ttf", 28);

    std::string message("Congratulations! You have successfully completed the level!");

    SDL_Color color_white = { 255, 255, 255 };
    SDL_Surface* surface_message = TTF_RenderText_Blended_Wrapped(font, message.c_str(), color_white, DEFAULT_WIDTH - 20);
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(m_renderer, surface_message);

    int text_width = 0;
    int text_height = 0;
    SDL_QueryTexture(texture_message, NULL, NULL, &text_width, &text_height);
    SDL_Rect dstrect = { 20, 15, text_width, text_height };

    SDL_RenderCopy(m_renderer, texture_message, NULL, &dstrect);

    TTF_CloseFont(font);
    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);
}


window_win::~window_win() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}


void window_win::show() {
    SDL_RenderPresent(m_renderer);

    SDL_Event event;
    std::memset((void*)&event, 0x00, sizeof(SDL_Event));

    bool window_active = true;
    while (window_active) {
        auto frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type != SDL_WINDOWEVENT) {
                continue;
            }

            switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                window_active = false;
                return;

            default:
                break;
            }
        }

        auto frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 20)  {
            SDL_Delay((int)(20 - frameTime));
        }
    }
}
