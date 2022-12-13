#include "monster.h"


monster::monster(const char p_id, const level_map* p_map, const int p_cell_size, const position p_initial_position) :
    m_id(p_id),
    m_map(p_map),
    m_cell_size(p_cell_size),
    m_current_position(p_initial_position)
{ }


char monster::get_id() const {
    return m_id;
}


position monster::get_current_position() const {
    return m_current_position;
}


position monster::get_next_position() const {
    return m_next_position;
}


position monster::get_current_scale_position() const {
    return m_current_position * m_cell_size + m_transition_step;
}


position monster::get_next_scale_position() const {
    return m_next_position * m_cell_size;
}


std::vector<position> monster::get_possible_steps(const position& p_pos) const {
    std::vector<position> positions = { };
    if ((*m_map)[p_pos.y][p_pos.x + 1] != '*') {
        positions.push_back({ p_pos.x + 1, p_pos.y });
    }

    if ((*m_map)[p_pos.y][p_pos.x - 1] != '*') {
        positions.push_back({ p_pos.x - 1, p_pos.y });
    }

    if ((*m_map)[p_pos.y + 1][p_pos.x] != '*') {
        positions.push_back({ p_pos.x, p_pos.y + 1 });
    }

    if ((*m_map)[p_pos.y - 1][p_pos.x] != '*') {
        positions.push_back({ p_pos.x, p_pos.y - 1 });
    }

    return positions;
}


void monster::handle_state() {
    switch (m_state) {
    case monster_state::cell_transition:
        handle_transition();
        break;

    case monster_state::wait_for_input:
        handle_wait_for_input();
        break;

    default:
        break;
    }
}


void monster::handle_transition() {
    const auto next_pos_scale = get_next_scale_position();
    const auto cur_pos_scale = get_current_scale_position();

    if (cur_pos_scale.x != next_pos_scale.x) {
        if (cur_pos_scale.x > next_pos_scale.x) {
            m_transition_step.x -= TRANSITION_STEP_SIZE;
            if (m_transition_step.x < -m_cell_size) {
                m_transition_step.x = -m_cell_size;
            }
        }
        else {
            m_transition_step.x += TRANSITION_STEP_SIZE;

            if (m_transition_step.x > m_cell_size) {
                m_transition_step.x = m_cell_size;
            }
        }
    }
    else if (cur_pos_scale.y != next_pos_scale.y) {
        if (cur_pos_scale.y > next_pos_scale.y) {
            m_transition_step.y -= TRANSITION_STEP_SIZE;

            if (m_transition_step.y < -m_cell_size) {
                m_transition_step.y = -m_cell_size;
            }
        }
        else {
            m_transition_step.y += TRANSITION_STEP_SIZE;

            if (m_transition_step.y > m_cell_size) {
                m_transition_step.y = m_cell_size;
            }
        }
    }

    if (get_current_scale_position() == next_pos_scale) {
        m_state = monster_state::wait_for_input;
        m_current_position = m_next_position;
        m_transition_step = { 0, 0 };
    }
}