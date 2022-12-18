#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>


class texture_manager {
private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_textures;

public:
    texture_manager(SDL_Renderer* p_renderer);

    ~texture_manager();

public:
    void load(const std::string& p_path);

    void draw(const SDL_Rect& p_dest) const;

    void draw_frame(const SDL_Rect& p_dest, const int current_row, const int current_frame, const SDL_RendererFlip flip) const;

};