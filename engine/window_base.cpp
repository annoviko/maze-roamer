#include "window_base.h"


void window_base::show() {
    SDL_RenderPresent(m_renderer);

    SDL_Event event;
    std::memset((void*)&event, 0x00, sizeof(SDL_Event));

    bool window_active = true;
    while (window_active) {
        auto frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                window_active = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                case SDLK_SPACE:
                case SDLK_ESCAPE:
                    window_active = false;
                    break;
                }

            default:
                break;
            }
        }

        auto frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 20) {
            SDL_Delay((int)(20 - frameTime));
        }
    }
}


void window_base::draw_window_border() {
    SDL_SetRenderDrawColor(m_renderer, BORDER_COLOR.r, BORDER_COLOR.g, BORDER_COLOR.b, BORDER_COLOR.a);

    SDL_RenderDrawLine(m_renderer, m_x, m_y, m_x + m_width, m_y);
    SDL_RenderDrawLine(m_renderer, m_x, m_y, m_x, m_y + m_height);
    SDL_RenderDrawLine(m_renderer, m_x + m_width, m_y, m_x + m_width, m_y + m_height);
    SDL_RenderDrawLine(m_renderer, m_x, m_y + m_height, m_x + m_width, m_y + m_height);
}
