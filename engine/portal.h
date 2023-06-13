#pragma once


#pragma once


#include "core/game_object.h"


class portal : public game_object {
private:
    constexpr static int AMOUNT_FRAMES = 4;

public:
    constexpr static int SPRITE_ROW = 5;
    constexpr static int SPRITE_COL = 16;

public:
    portal(const char p_id, const SDL_Rect& p_location, const position& p_logical_location, const texture_manager& p_manager, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
        game_object(p_id, p_location, p_logical_location, p_manager, p_current_row, p_current_frame, p_num_of_frame, p_flip)
    {
        m_current_row = SPRITE_ROW;
        m_current_frame = SPRITE_COL;

        m_location.y -= 32;
        m_location.w = 64;
        m_location.h = 64;
    }

public:
    void update() override { }

    void render() override {
        m_current_frame = static_cast<int>((SDL_GetTicks() / 200) % AMOUNT_FRAMES) * 2 + SPRITE_COL;

        SDL_Rect source = { m_current_frame * 32, SPRITE_ROW * 32, 64, 64 };
        m_texture_manager.draw_frame(source, m_location, SDL_FLIP_NONE);
    }
};