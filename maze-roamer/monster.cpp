#include "monster.h"


monster::monster(const char p_id, const level_map* p_map, const int p_cell_size, const position p_initial_position) :
    m_id(p_id),
    m_map(p_map),
    m_cell_size(p_cell_size),
    m_current_position(p_initial_position),
    m_prev_position(p_initial_position)
{ }


char monster::get_id() const {
    return m_id;
}


position monster::get_previous_position() const {
    return m_prev_position;
}


position monster::get_current_position() const {
    return m_current_position;
}


position monster::get_previous_scale_position() const {
    return {};
}

position monster::get_current_scale_position() const {
    return {};
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