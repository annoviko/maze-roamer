#pragma once


#include "core/graphic_context.h"
#include "core/rgba.h"


class window_base {
protected:
    constexpr static int DEFAULT_HEIGHT = 160;
    constexpr static int DEFAULT_WIDTH = 640;

    constexpr static rgba BACKGROUND_COLOR = { 0xff, 0x5b, 0x00, 0xff };
    constexpr static rgba BORDER_COLOR = { 0xff, 0xff, 0xff, 0xff };

    constexpr static char FONTNAME[] = "fonts/the-confession-full-regular.ttf";
    constexpr static std::uint8_t FONTSIZE = 28;

protected:
    int m_x = graphic_context::get().get_window_x_center(DEFAULT_WIDTH);
    int m_y = graphic_context::get().get_window_y_center(DEFAULT_HEIGHT);
    int m_width = DEFAULT_WIDTH;
    int m_height = DEFAULT_HEIGHT;

    SDL_Renderer* m_renderer = graphic_context::get().get_render();

public:
    window_base() = default;

    virtual ~window_base() = default;

public:
    virtual void show();

protected:
    virtual void draw_window_border();
};
