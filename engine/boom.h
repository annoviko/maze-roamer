#pragma once


#include "core/game_object_interim.h"


class boom : public game_object_interim {
private:
    constexpr static int INITIAL_FRAME = 9;
    constexpr static int AMOUNT_FRAMES = 4;

public:
    boom(const char p_id, const SDL_Rect& p_location, const position& p_logical_location, const texture_manager& p_manager, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
        game_object_interim(p_id, p_location, p_logical_location, p_manager, 100, p_current_row, p_current_frame, p_num_of_frame, p_flip)
    {
        m_current_row = 6;
        m_current_frame = INITIAL_FRAME;
    }

public:
    void update() override { }

    void render() override {
        if (!m_timer.is_active()) {
            m_current_frame++;

            if (m_current_frame < INITIAL_FRAME + AMOUNT_FRAMES) {
                m_timer.activate(true, 100);
            }
        }

        if (!is_expired()) {
            game_object::render();
        }
    }

    bool is_expired() override {
        return m_current_frame > INITIAL_FRAME + AMOUNT_FRAMES;
    }
};
