#pragma once


#include <string>

#include <SDL.h>

#include "core/rgba.h"


class window_message {
private:
    constexpr static int DEFAULT_HEIGHT = 160;
    constexpr static int DEFAULT_WIDTH = 640;

    constexpr static rgba BACKGROUND_COLOR = { 0xff, 0x5b, 0x00, 0xff };

    constexpr static char FONTNAME[] = "fonts/Symtext.ttf";
    constexpr static std::uint8_t FONTSIZE = 28;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

public:
    window_message(const std::string& p_title, const std::string& p_message);

    virtual ~window_message();

public:
    virtual void show();
};