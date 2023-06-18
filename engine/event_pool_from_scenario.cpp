#include "event_pool_from_scenario.h"


void event_pool_from_scenario::push(const event_from_scenario& p_event) {
    m_pool.push(p_event);
}


event_from_scenario event_pool_from_scenario::pop() {
    event_from_scenario cur_event = m_pool.front();
    m_pool.pop();
    return cur_event;
}


bool event_pool_from_scenario::is_empty() const {
    return m_pool.empty();
}


void event_pool_from_scenario::clear() {
    m_pool = { };
}