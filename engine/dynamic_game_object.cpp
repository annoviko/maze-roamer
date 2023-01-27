#include "dynamic_game_object.h"


dynamic_game_object::dynamic_game_object(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position, const int p_transition_step_size = TRANSITION_STEP_SIZE, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
    game_object(p_id, p_location, p_logical_position, p_texture_manager, p_current_row, p_current_frame, p_num_of_frame, p_flip),
    m_map(p_map),
    m_logical_destination(p_logical_position),
    m_destination(p_location),
    m_transition_step_size(p_transition_step_size)
{ }


void dynamic_game_object::set_transition_step(const int p_transition_step) {
    m_transition_step_size = p_transition_step;
}


int dynamic_game_object::get_transition_step() const {
    return m_transition_step_size;
}


bool dynamic_game_object::is_collision(const dynamic_game_object& p_other) const {
    return m_logical_location == p_other.m_logical_location;
}


bool dynamic_game_object::is_collision(const position& p_logical_position) const {
    return m_logical_location == p_logical_position;
}


std::vector<position> dynamic_game_object::get_possible_steps(const int x, const int y) const {
    std::vector<position> positions = { };
    if ((*m_map)[y][x + 1] != '*') {
        positions.push_back({ x + 1, y });
    }

    if ((*m_map)[y][x - 1] != '*') {
        positions.push_back({ x - 1, y });
    }

    if ((*m_map)[y + 1][x] != '*') {
        positions.push_back({ x, y + 1 });
    }

    if ((*m_map)[y - 1][x] != '*') {
        positions.push_back({ x, y - 1 });
    }

    return positions;
}


std::vector<position> dynamic_game_object::get_possible_steps(const position& p_pos) const {
    return get_possible_steps(p_pos.x, p_pos.y);
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


void dynamic_game_object::set_state(const dynamic_object_state p_state) {
    m_state = p_state;
}


void dynamic_game_object::define_moving_state() {
    if (m_logical_location.x < m_logical_destination.x) {
        set_state(dynamic_object_state::moving_right);
    }
    else if (m_logical_location.x > m_logical_destination.x) {
        set_state(dynamic_object_state::moving_left);
    }
    else if (m_logical_location.y < m_logical_destination.y) {
        set_state(dynamic_object_state::moving_down);
    }
    else if (m_logical_location.y > m_logical_destination.y) {
        set_state(dynamic_object_state::moving_up);
    }
    else {
        set_state(dynamic_object_state::wait_for_destination);
    }
}


void dynamic_game_object::handle_moving_done() {
    m_location = m_destination;

    m_state = dynamic_object_state::wait_for_destination;
    m_logical_location = m_logical_destination;
}


void dynamic_game_object::handle_moving_left() {
    m_location.x -= m_transition_step_size;
    if (m_location.x <= m_destination.x) {
        handle_moving_done();
    }
}


void dynamic_game_object::handle_moving_right() {
    m_location.x += m_transition_step_size;
    if (m_location.x >= m_destination.x) {
        handle_moving_done();
    }
}


void dynamic_game_object::handle_moving_up() {
    m_location.y -= m_transition_step_size;
    if (m_location.y <= m_destination.y) {
        handle_moving_done();
    }
}


void dynamic_game_object::handle_moving_down() {
    m_location.y += m_transition_step_size;
    if (m_location.y >= m_destination.y) {
        handle_moving_done();
    }
}
