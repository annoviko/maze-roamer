#include "monster_random.h"


void monster_random::update() {
    handle_state();
}


void monster_random::handle_wait_for_destination() {
    auto ways = get_possible_steps(m_logical_location);
    std::size_t index_way = rand() % ways.size();

    m_logical_destination = ways[index_way];
    m_destination.x = m_logical_destination.x * m_destination.w;
    m_destination.y = m_logical_destination.y * m_destination.h;

    define_moving_state();
    if (m_state != dynamic_object_state::wait_for_destination) {
        handle_state();
    }
}
