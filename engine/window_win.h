#pragma once


#include <SDL.h>


class window_win {
private:
    constexpr static int DEFAULT_HEIGHT = 160;
    constexpr static int DEFAULT_WIDTH = 640;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

public:
    window_win();

    ~window_win();

public:
    void show();
};