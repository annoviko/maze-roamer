#include "dynamic_game_object.h"


dynamic_game_object::dynamic_game_object(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
    game_object(p_id, p_location, p_texture_manager, p_current_row, p_current_frame, p_num_of_frame, p_flip),
    m_map(p_map),
    m_logical_location(p_logical_position),
    m_logical_destination(p_logical_position),
    m_destination(p_location)
{ }


const position& dynamic_game_object::get_logical_location() const {
    return m_logical_location;
}


std::vector<position> dynamic_game_object::get_possible_steps(const position& p_pos) const {
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


void dynamic_game_object::handle_state() {
    switch (m_state) {
    case dynamic_object_state::moving_up:
        handle_moving_up();
        break;

    case dynamic_object_state::moving_down:
        handle_moving_down();
        break;

    case dynamic_object_state::moving_left:
        handle_moving_left();
        break;

    case dynamic_object_state::moving_right:
        handle_moving_right();
        break;

    case dynamic_object_state::wait_for_destination:
        handle_wait_for_destination();
        break;

    default:
        break;
    }
}


void dynamic_game_object::define_moving_state() {
    if (m_logical_location.x < m_logical_destination.x) {
        m_state = dynamic_object_state::moving_right;
    }
    else if (m_logical_location.x > m_logical_destination.x) {
        m_state = dynamic_object_state::moving_left;
    }
    else if (m_logical_location.y < m_logical_destination.y) {
        m_state = dynamic_object_state::moving_down;
    }
    else if (m_logical_location.y > m_logical_destination.y) {
        m_state = dynamic_object_state::moving_up;
    }
    else {
        m_state = dynamic_object_state::wait_for_destination;
    }
}


void dynamic_game_object::handle_moving_done() {
    m_location = m_destination;

    m_state = dynamic_object_state::wait_for_destination;
    m_logical_location = m_logical_destination;
}


void dynamic_game_object::handle_moving_left() {
    m_location.x -= TRANSITION_STEP_SIZE;
    if (m_location.x <= m_destination.x) {
        handle_moving_done();
    }
}


void dynamic_game_object::handle_moving_right() {
    m_location.x += TRANSITION_STEP_SIZE;
    if (m_location.x >= m_destination.x) {
        handle_moving_done();
    }
}


void dynamic_game_object::handle_moving_up() {
    m_location.y -= TRANSITION_STEP_SIZE;
    if (m_location.y <= m_destination.y) {
        handle_moving_done();
    }
}


void dynamic_game_object::handle_moving_down() {
    m_location.y += TRANSITION_STEP_SIZE;
    if (m_location.y >= m_destination.y) {
        handle_moving_done();
    }
}
