#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>


class texture_manager {
private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_textures;

    int m_offset_x = 0;
    int m_offset_y = 0;

public:
    texture_manager(SDL_Renderer* p_renderer, const int p_offset_x = 0, const int p_offset_y = 0);

    ~texture_manager();

public:
    void set_offset(const int p_offset_x, const int p_offset_y);

    void load(const std::string& p_path);

    void draw(const SDL_Rect& p_dest) const;

    void draw_frame(const SDL_Rect& p_dest, const int current_row, const int current_frame, const SDL_RendererFlip flip) const;

    void draw_frame_wo_offset(const SDL_Rect& p_dest, const int current_row, const int current_frame, const SDL_RendererFlip flip) const;
};