#include "monster_random.h"


position monster_random::move(const position& p_player) {
    (void)p_player;

    handle_state();

    return m_current_position;
}


void monster_random::handle_wait_for_input() {
    auto ways = get_possible_steps(m_current_position);
    std::size_t index_way = rand() % ways.size();

    m_next_position = ways[index_way];

    m_state = monster_state::cell_transition;

    handle_transition(); // make single stop just not to stay for 2 iterations on the same place
}
