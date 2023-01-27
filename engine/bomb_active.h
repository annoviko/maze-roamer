#pragma once


#include "core/game_object_interim.h"


class bomb_active : public game_object_interim {
public:
    bomb_active(const char p_id, const SDL_Rect& p_location, const position& p_logical_location, const texture_manager& p_manager, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
        game_object_interim(p_id, p_location, p_logical_location, p_manager, 5000, p_current_row, p_current_frame, p_num_of_frame, p_flip)
    {
        m_current_row = 6;
        m_current_frame = 7;
    }

public:
    void update() override { }

    void render() override {
        m_current_frame = static_cast<int>((SDL_GetTicks() / 200) % 2) + 7;
        game_object::render();
    }
};
