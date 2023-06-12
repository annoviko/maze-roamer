#include "texture_manager.h"

#include <filesystem>


texture_manager::texture_manager(SDL_Renderer* p_renderer, const int p_offset_x, const int p_offset_y) :
    m_renderer(p_renderer),
    m_offset_x(p_offset_x),
    m_offset_y(p_offset_y)
{ }


texture_manager::~texture_manager() {
    SDL_DestroyTexture(m_textures);
}


void texture_manager::set_offset(const int p_offset_x, const int p_offset_y) {
    m_offset_x = p_offset_x;
    m_offset_y = p_offset_y;
}


void texture_manager::load(const std::string& p_path) {
    if (!std::filesystem::exists(p_path)) {
        throw std::invalid_argument("Impossible to load texture (reason: file does not exist).");
    }

    SDL_Texture* texture = IMG_LoadTexture(m_renderer, p_path.c_str());
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    m_textures = texture;
}


void texture_manager::draw(const SDL_Rect& p_dest) const {
    SDL_RenderCopy(m_renderer, m_textures, nullptr, &p_dest);
}


void texture_manager::draw_frame(const SDL_Rect& p_dest, const int current_row, const int current_frame, const SDL_RendererFlip flip) const {
    const SDL_Rect src_rect = { p_dest.w * current_frame , p_dest.h * (current_row - 1), p_dest.w, p_dest.h };
    const SDL_Rect dest_rect = { p_dest.x + m_offset_x, p_dest.y + m_offset_y, p_dest.w, p_dest.h };
    SDL_RenderCopyEx(m_renderer, m_textures, &src_rect, &dest_rect, 0, nullptr, flip);
}


void texture_manager::draw_frame(const SDL_Rect& p_src, const SDL_Rect& p_dest, const SDL_RendererFlip flip) const {
    const SDL_Rect dest_rect = { p_dest.x + m_offset_x, p_dest.y + m_offset_y, p_dest.w, p_dest.h };
    SDL_RenderCopyEx(m_renderer, m_textures, &p_src, &dest_rect, 0, nullptr, flip);
}


void texture_manager::draw_frame_wo_offset(const SDL_Rect& p_dest, const int current_row, const int current_frame, const SDL_RendererFlip flip) const {
    const SDL_Rect src_rect = { p_dest.w * current_frame , p_dest.h * (current_row - 1), p_dest.w, p_dest.h };
    const SDL_Rect dest_rect = { p_dest.x, p_dest.y, p_dest.w, p_dest.h };
    SDL_RenderCopyEx(m_renderer, m_textures, &src_rect, &dest_rect, 0, nullptr, flip);
}


void texture_manager::draw_frame_wo_offset(const SDL_Rect& p_src, const SDL_Rect& p_dest, const SDL_RendererFlip flip) const {
    SDL_RenderCopyEx(m_renderer, m_textures, &p_src, &p_dest, 0, nullptr, flip);
}