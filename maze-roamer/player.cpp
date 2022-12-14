#include "player.h"


void player::move_right() {
    m_next_state = dynamic_object_state::moving_right;
}


void player::move_up() {
    m_next_state = dynamic_object_state::moving_up;
}


void player::move_left() {
    m_next_state = dynamic_object_state::moving_left;
}


void player::move_down() {
    m_next_state = dynamic_object_state::moving_down;
}


void player::update() {
    if (m_next_state != m_state) {
        try_change_destination(m_next_state);
    }

    handle_state();
}


void player::try_change_destination(const dynamic_object_state p_state) {
    position destination_candidate = m_logical_location;

    switch (p_state) {
    case dynamic_object_state::moving_left:
        destination_candidate.x--;
        break;

    case dynamic_object_state::moving_right:
        destination_candidate.x++;
        break;

    case dynamic_object_state::moving_up:
        destination_candidate.y--;
        break;

    case dynamic_object_state::moving_down:
        destination_candidate.y++;
        break;
    }

    if ((*m_map)[destination_candidate.y][destination_candidate.x] != '*') {
        m_logical_destination = destination_candidate;
        
        m_destination.x = destination_candidate.x * m_location.w;
        m_destination.y = destination_candidate.y * m_location.h;

        m_state = p_state;
        m_last_state = p_state;
    }
}


void player::handle_wait_for_destination() {
    try_change_destination(m_last_state);
}
