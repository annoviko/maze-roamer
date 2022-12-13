#include "texture_manager.h"

#include <filesystem>


texture_manager::texture_manager(SDL_Renderer* p_renderer) :
    m_renderer(p_renderer)
{ }


texture_manager::~texture_manager() {
    for (const auto& pair : m_textures) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }

    m_textures.clear();
}


void texture_manager::load(const char p_id, const std::string& p_path) {
    if (!std::filesystem::exists(p_path)) {
        throw std::invalid_argument("Impossible to load texture (reason: file does not exist).");
    }

    SDL_Texture* texture = IMG_LoadTexture(m_renderer, p_path.c_str());
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    m_textures[p_id] = texture;
}


void texture_manager::draw(const char p_id, const SDL_Rect& p_dest) const {
    auto iter_texture = m_textures.find(p_id);
    if (iter_texture == m_textures.cend()) {
        throw std::invalid_argument("Impossible to draw texture (reason: id is not found).");
    }

    SDL_RenderCopy(m_renderer, iter_texture->second, nullptr, &p_dest);
}
