#pragma once

#include "game_object.h"
#include "interim.h"


class game_object_interim : public game_object {
public:
    using ptr = std::shared_ptr<game_object_interim>;

protected:
    interim<bool> m_timer;

public:
    game_object_interim(const char p_id, const SDL_Rect& p_location, const position& p_logical_location, const texture_manager& p_manager, const int lifetime_ms, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
        game_object(p_id, p_location, p_logical_location, p_manager, p_current_row, p_current_frame, p_num_of_frame, p_flip)
    {
        m_timer.activate(true, lifetime_ms);
    }

public:
    void update() override {
        m_timer.is_active();
    }

    virtual bool is_expired() {
        return !m_timer.is_active();
    }
};
