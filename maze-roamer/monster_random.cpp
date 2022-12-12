#include "monster_random.h"


position monster_random::move(const position& p_player) {
    (void)p_player;

    handle_state();

    return m_current_position;
}


void monster_random::handle_state() {
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


void monster_random::handle_wait_for_input() {
    m_prev_position = m_current_position;

    auto ways = get_possible_steps(m_current_position);
    std::size_t index_way = rand() % ways.size();

    m_next_position = ways[index_way];

    m_state = monster_state::cell_transition;

    handle_transition(); // make single stop just not to stay for 2 iterations on the same place
}


void monster_random::handle_transition() {
    if (m_current_position.x != m_next_position.x) {
        if (m_current_position.x > m_next_position.x) {
            m_current_position.x--;
        }
        else {
            m_current_position.x++;
        }
    }
    else if (m_current_position.y != m_next_position.y) {
        if (m_current_position.y > m_next_position.y) {
            m_current_position.y--;
        }
        else {
            m_current_position.y++;
        }
    }

    m_state = (m_current_position == m_next_position) ? monster_state::wait_for_input : monster_state::cell_transition;
}
