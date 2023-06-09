#include "painter.h"


painter::painter(SDL_Renderer* p_renderer) :
    m_renderer(p_renderer)
{ }


void painter::draw_frame(const SDL_Rect& p_rect) {
    SDL_RenderDrawLine(m_renderer, p_rect.x, p_rect.y, p_rect.x + p_rect.w, p_rect.y);
    SDL_RenderDrawLine(m_renderer, p_rect.x, p_rect.y, p_rect.x, p_rect.y + p_rect.h);
    SDL_RenderDrawLine(m_renderer, p_rect.x + p_rect.w, p_rect.y, p_rect.x + p_rect.w, p_rect.y + p_rect.h);
    SDL_RenderDrawLine(m_renderer, p_rect.x, p_rect.y + p_rect.h, p_rect.x + p_rect.w, p_rect.y + p_rect.h);
}


void painter::draw_frame(const SDL_Rect& p_rect, const rgba& p_rgba) {
    SDL_SetRenderDrawColor(m_renderer, p_rgba.r, p_rgba.g, p_rgba.b, p_rgba.a);
    draw_frame(p_rect);
}


void painter::draw_rectangle(const SDL_Rect& p_rect) {
    SDL_RenderFillRect(m_renderer, &p_rect);
}


void painter::draw_rectangle(const SDL_Rect& p_rect, const rgba& p_rgba) {
    SDL_SetRenderDrawColor(m_renderer, p_rgba.r, p_rgba.g, p_rgba.b, p_rgba.a);
    draw_rectangle(p_rect);
}


void painter::draw_text(const std::string& p_text, const font_value_t p_font, const int p_font_size, const rgba& p_rgba, 
    const int p_x, const int p_y,
    const int p_align_width,
    const text_alignment p_x_align,
    const int p_align_height,
    const text_alignment p_y_align)
{
    TTF_Font* font = font_manager::get().get_font(p_font, p_font_size);
    
    SDL_Color* sdl_color = (SDL_Color *)&p_rgba;
    SDL_Surface* surface_message = TTF_RenderText_Solid(font, p_text.c_str(), *sdl_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(m_renderer, surface_message);

    int text_width = 0;
    int text_height = 0;
    SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);

    int text_x = p_x;
    int text_y = p_y;

    if (p_align_width != -1) {
        text_x += align_text_position(p_align_width, text_width,  p_x_align);
    }

    if (p_align_height != -1) {
        text_y += align_text_position(p_align_height, text_height,  p_y_align);
    }

    SDL_Rect text_texture_position = { text_x, text_y, text_width, text_height };

    SDL_RenderCopy(m_renderer, text_texture, NULL, &text_texture_position);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(text_texture);
}


int painter::align_text_position(const int p_field_length, const int p_text_length, const text_alignment p_align) {
    switch (p_align) {
    case text_alignment::CENTER:
        return (p_field_length - p_text_length) / 2;

    case text_alignment::LEFT:
    case text_alignment::TOP:
        return 0;

    case text_alignment::RIGHT:
    case text_alignment::BOTTOM:
        return p_field_length - p_text_length;
    }

    return 0;
}