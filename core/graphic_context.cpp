#include "graphic_context.h"
#include "graphic_error.h"


graphic_context::~graphic_context() {
    TTF_Quit();
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void graphic_context::intialize(const std::string& p_application_name) {
    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_GetDesktopDisplayMode(0, &m_display_mode) != 0) {
        const std::string message = std::string("Unable to get desktop display mode: ") + std::string(SDL_GetError());
        throw graphic_error("Unable to get desktop display mode: " + std::string(SDL_GetError()));
    }

    m_window = SDL_CreateWindow(p_application_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_display_mode.w, m_display_mode.h, SDL_WINDOW_FULLSCREEN);
    if (m_window == nullptr) {
        throw graphic_error("Unable to create window: " + std::string(SDL_GetError()));
    }

    m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_render == nullptr) {
        throw graphic_error("Unable to create renderer: " + std::string(SDL_GetError()));
    }

    if (TTF_Init() < 0) {
        throw graphic_error("Error initializing SDL_ttf: " + std::string(TTF_GetError()));
    }
}


const int graphic_context::get_screen_width() const {
    return m_display_mode.w;
}

const int graphic_context::get_screen_height() const {
    return m_display_mode.h;
}

SDL_Window* graphic_context::get_window() {
    return m_window;
}

SDL_Renderer* graphic_context::get_render() {
    return m_render;
}