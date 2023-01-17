#include "game_object.h"


game_object::game_object(const char p_id, const SDL_Rect& p_location, const position& p_logical_position, const texture_manager& p_manager, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
    m_id(p_id),
    m_texture_manager(p_manager),
    m_location(p_location),
    m_logical_location(p_logical_position),
    m_current_row(p_current_row),
    m_current_frame(p_current_frame),
    m_num_of_frame(p_num_of_frame),
    m_flip(p_flip)
{ }


char game_object::get_id() const {
    return m_id;
}


void game_object::render() {
    if (m_current_row == 1 && m_current_frame == 0 && m_num_of_frame == 0 && m_flip == SDL_FLIP_NONE) {
        m_texture_manager.draw(m_location);
    }
    else
    {
        m_texture_manager.draw_frame(m_location, m_current_row, m_current_frame, m_flip);
    }
}


const position& game_object::get_logical_location() const {
    return m_logical_location;
}
