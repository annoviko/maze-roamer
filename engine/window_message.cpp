#include "window_message.h"


#include <exception>
#include <string>

#include "core/font.h"


window_message::window_message(const std::string& p_message, const bool p_resize_to_message) :
    window_base()
{
    font message_font = font(FONTNAME, FONTSIZE);

    std::string message(p_message);

    SDL_Color color_white = { 255, 255, 255 };
    SDL_Surface* surface_message = TTF_RenderText_Blended_Wrapped(message_font(), message.c_str(), color_white, DEFAULT_WIDTH - 20);
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(m_renderer, surface_message);

    int text_width = 0;
    int text_height = 0;
    SDL_QueryTexture(texture_message, NULL, NULL, &text_width, &text_height);

    if (p_resize_to_message) {
        m_width = text_width + 40;
        m_height = text_height + 30;
        m_x = graphic_context::get().get_window_x_center(m_width);
        m_y = graphic_context::get().get_window_y_center(m_height);
    }

    SDL_Rect rect = {
        m_x,
        m_y,
        m_width,
        m_height
    };

    SDL_SetRenderDrawColor(m_renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
    SDL_RenderFillRect(m_renderer, &rect);

    SDL_Rect dstrect = { m_x + 20, m_y + 15, text_width, text_height };
    SDL_RenderCopy(m_renderer, texture_message, NULL, &dstrect);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);

    draw_window_border();
}
