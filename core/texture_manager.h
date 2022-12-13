#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>


class texture_manager {
private:
    SDL_Renderer* m_renderer;
    std::map<char, SDL_Texture*> m_textures;

public:
    texture_manager(SDL_Renderer* p_renderer);

    ~texture_manager();

public:
    void load(const char p_id, const std::string& p_path);

    void draw(const char p_id, const SDL_Rect& p_dest);
};