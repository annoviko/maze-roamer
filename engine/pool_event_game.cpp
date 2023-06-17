#include "pool_event_game.h"


void pool_event_game::push(const event_from_game& p_event) {
    m_pool.push(p_event);
}


event_from_game pool_event_game::pop() {
    event_from_game cur_event = m_pool.front();
    m_pool.pop();
    return cur_event;
}


bool pool_event_game::is_empty() const {
    return m_pool.empty();
}


void pool_event_game::clear() {
    m_pool = { };
}