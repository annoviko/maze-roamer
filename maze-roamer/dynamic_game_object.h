#pragma once


#include <vector>
#include <string>

#include "level_matrix.h"
#include "dynamic_object_state.h"

#include "core/game_object.h"
#include "core/position.h"
#include "core/texture_manager.h"


class dynamic_game_object : public game_object {
protected:
    static constexpr int TRANSITION_STEP_SIZE = 1;

protected:
    const level_matrix* m_map;

    dynamic_object_state m_state = dynamic_object_state::wait_for_destination;

    position m_logical_location = { -1, -1 };
    position m_logical_destination = { -1, -1 };

    SDL_Rect m_destination;

    int m_transition_step_size = TRANSITION_STEP_SIZE;

public:
    dynamic_game_object(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map,
        const position p_logical_position,
        const int p_transition_step_size,
        const int p_current_row,
        const int p_current_frame,
        const int p_num_of_frame,
        const SDL_RendererFlip p_flip);

public:
    const position& get_logical_location() const;

    bool is_collision(const dynamic_game_object& p_other) const;

protected:
    virtual std::vector<position> get_possible_steps(const position& p_pos) const;

    virtual void handle_state();

    virtual void define_moving_state();

    virtual void handle_moving_done();

    virtual void handle_moving_left();

    virtual void handle_moving_right();

    virtual void handle_moving_up();

    virtual void handle_moving_down();

    virtual void handle_wait_for_destination() = 0;
};