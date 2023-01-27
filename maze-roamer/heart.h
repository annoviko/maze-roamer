#pragma once

#pragma once

#include "core/game_object.h"


class heart : public game_object {
public:
    heart(const char p_id, const SDL_Rect& p_location, const texture_manager& p_manager, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
        game_object(p_id, p_location, p_manager, p_current_row, p_current_frame, p_num_of_frame, p_flip)
    {
        m_current_row = 9; // TODO
        m_current_frame = 2; // TODO
    }

public:
    void update() override
    {

    }
};