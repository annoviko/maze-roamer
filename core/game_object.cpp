#include "game_object.h"


game_object::game_object(const char p_id, const SDL_Rect& p_location, const texture_manager& p_manager) :
    m_id(p_id),
    m_texture_manager(p_manager),
    m_location(p_location)
{ }


char game_object::get_id() const {
    return m_id;
}


void game_object::render() {
    m_texture_manager.draw(m_id, m_location);
}
