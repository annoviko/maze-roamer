#pragma once


#include <SDL.h>
#include <SDL_ttf.h>

#include "singleton.h"
#include "texture_manager.h"


class graphic_context : public singleton<graphic_context> {
private:
    SDL_DisplayMode m_display_mode;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_render = nullptr;

public:
    graphic_context() = default;

    ~graphic_context();

public:
    void intialize(const std::string& p_application_name);

    const int get_screen_width() const;

    const int get_screen_height() const;

    const int get_window_x_center(const int p_width) const;

    const int get_window_y_center(const int p_height) const;

    SDL_Window* get_window();

    SDL_Renderer* get_render();
};
