#pragma once


#include "core/game_object.h"


class coin_silver : public game_object {
private:
    constexpr static int AMOUNT_FRAMES = 4;

public:
    constexpr static int SPRITE_ROW = 9;
    constexpr static int SPRITE_COL = 4;

    constexpr static int COIN_VALUE = 1;

public:
    coin_silver(const char p_id, const SDL_Rect& p_location, const position& p_logical_location, const texture_manager& p_manager, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
        game_object(p_id, p_location, p_logical_location, p_manager, p_current_row, p_current_frame, p_num_of_frame, p_flip)
    {
        m_current_row = SPRITE_ROW;
        m_current_frame = SPRITE_COL;
    }

public:
    void update() override { }

    void render() override {
        m_current_frame = static_cast<int>((SDL_GetTicks() / 200) % AMOUNT_FRAMES) + SPRITE_COL;
        game_object::render();
    }
};