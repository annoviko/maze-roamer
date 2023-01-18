#pragma once


#include <chrono>

#include "booster_interim.h"
#include "dynamic_game_object.h"
#include "player_context.h"


class player : public dynamic_game_object {
private:
    static constexpr int PLAYER_TRANSITION_STEP_SIZE = 2;

private:
    dynamic_object_state m_last_state = dynamic_object_state::wait_for_destination;

    dynamic_object_state m_next_state = dynamic_object_state::wait_for_destination;

    player_context::ptr m_player_context;

public:
    player(const char p_id, 
        const SDL_Rect& p_location, 
        const texture_manager& p_texture_manager, 
        const player_context::ptr& p_player_context,
        const level_matrix* p_map, 
        const position p_logical_position, 
        const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, 
        const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :

        dynamic_game_object(p_id, p_location, p_texture_manager, p_map, p_logical_position, PLAYER_TRANSITION_STEP_SIZE, p_current_row, p_current_frame, p_num_of_frame, p_flip),
        m_player_context(p_player_context)
    {
        m_current_row = 5;
        m_num_of_frame = 4;
    }

public:
    void boost_speed(const int p_multiplier, const int p_duration_ms);

    void move_right();

    void move_up();

    void move_left();

    void move_down();

    bool death();

    void update() override;

    player_context::ptr get_context() const;

protected:
    void handle_boosters();

    void try_change_destination(const dynamic_object_state p_state);

    void handle_wait_for_destination() override;
};