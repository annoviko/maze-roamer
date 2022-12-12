#pragma once


#include <vector>
#include <string>

#include "level_map.h"
#include "monster_state.h"
#include "position.h"


class monster {
protected:
    static constexpr int TRANSITION_STEPS = 10;

protected:
    const level_map* m_map;
    const int m_cell_size;

    monster_state m_state = monster_state::wait_for_input;

    position m_next_position = { -1, -1 };
    position m_current_position = { -1, -1 };
    position m_prev_position = { -1, -1 };

    int m_transition_step = 0;

    char m_id;

public:
    monster(const char p_id, const level_map* p_map, const int p_cell_size, const position p_initial_position);

public:
    virtual char get_id() const;

    virtual position get_previous_position() const;

    virtual position get_current_position() const;

    virtual position get_previous_scale_position() const;

    virtual position get_current_scale_position() const;

    virtual std::vector<position> get_possible_steps(const position& p_pos) const;

    virtual position move(const position& p_player) = 0;
};