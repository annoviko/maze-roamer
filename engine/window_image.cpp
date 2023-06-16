#include "window_image.h"

#include <SDL_image.h>


window_image::window_image(const std::string& p_path) :
    window_base(),
    m_path(p_path)
{
    SDL_Surface* surface = IMG_Load(m_path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    SDL_QueryTexture(texture, NULL, NULL, &m_width, &m_height);

    m_x = graphic_context::get().get_window_x_center(m_width);
    m_y = graphic_context::get().get_window_y_center(m_height);

    SDL_Rect destinaton_location = { m_x, m_y, m_width, m_height };
    SDL_RenderCopy(m_renderer, texture, NULL, &destinaton_location);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    draw_window_border();
}
