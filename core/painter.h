#pragma once


#include <SDL.h>


#include "rgba.h"


class painter {
private:
    SDL_Renderer* m_renderer;

public:
    painter(SDL_Renderer* p_renderer);

public:
    void draw_frame(const SDL_Rect& p_rect);

    void draw_frame(const SDL_Rect& p_rect, const rgba& p_rgba);

    void draw_rectangle(const SDL_Rect& p_rect);

    void draw_rectangle(const SDL_Rect& p_rect, const rgba& p_rgba);
};