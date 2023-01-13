#include "monster_random.h"

void monster_random::update() {
    handle_state();
    int base_frame;
    switch (m_state)
    {
    case dynamic_object_state::moving_left:
        base_frame = 0;
        m_flip = SDL_FLIP_HORIZONTAL;
        break;
    case dynamic_object_state::moving_right:
        base_frame = 0;
        m_flip = SDL_FLIP_NONE;
        break;
    case dynamic_object_state::moving_down:
        base_frame = 9;
        m_flip = SDL_FLIP_NONE;
        break;
    case dynamic_object_state::moving_up:
        base_frame = 13;
        m_flip = SDL_FLIP_NONE;
        break;
    case dynamic_object_state::wait_for_destination:
    default:
        base_frame = 0;
        m_flip = SDL_FLIP_NONE;
    }
    m_current_frame = base_frame + int((SDL_GetTicks() / 100) % m_num_of_frame);
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
