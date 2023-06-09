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
