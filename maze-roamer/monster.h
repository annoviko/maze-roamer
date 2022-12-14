#pragma once


#include <vector>
#include <string>

#include "level_matrix.h"
#include "monster_state.h"

#include "core/game_object.h"
#include "core/position.h"
#include "core/texture_manager.h"


class monster : public game_object {
protected:
    static constexpr int TRANSITION_STEP_SIZE = 4;

protected:
    const level_matrix* m_map;

    monster_state m_state = monster_state::wait_for_destination;

    position m_logical_location = { -1, -1 };
    position m_logical_destination = { -1, -1 };

    SDL_Rect m_destination;

    position m_logical_player = { -1, -1 };

public:
    monster(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position);

public:
    void notify_player_moving(const position& p_pos);

    const position& get_logical_location() const;

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