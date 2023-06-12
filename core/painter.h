#pragma once


#include <string>

#include <SDL.h>

#include "font_manager.h"
#include "rgba.h"


enum class text_alignment {
    LEFT,
    CENTER,
    RIGHT,
    TOP,
    BOTTOM
};


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

    SDL_Rect draw_text(const std::string& p_text, const font_value_t p_font, const int p_font_size, const rgba& p_rgba,
        const int p_x, const int p_y,
        const int p_align_width = -1,
        const text_alignment p_x_align = text_alignment::CENTER,
        const int p_align_height = -1,
        const text_alignment p_y_align = text_alignment::CENTER);

private:
    int align_text_position(const int p_field_length, const int p_text_length, const text_alignment p_align);
};