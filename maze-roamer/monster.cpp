#include "monster.h"


monster::monster(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
    dynamic_game_object(p_id, p_location, p_texture_manager, p_map, p_logical_position, p_current_row, p_current_frame, p_num_of_frame, p_flip)
{ }


void monster::notify_player_moving(const position& p_pos) {
    m_logical_player = p_pos;
}
