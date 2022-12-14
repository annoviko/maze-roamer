#include "monster.h"


monster::monster(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position) :
    dynamic_game_object(p_id, p_location, p_texture_manager, p_map, p_logical_position)
{ }


void monster::notify_player_moving(const position& p_pos) {
    m_logical_player = p_pos;
}
