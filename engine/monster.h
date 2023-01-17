#pragma once


#include <vector>
#include <string>

#include "dynamic_game_object.h"



class monster : public dynamic_game_object {
protected:
    position m_logical_player = { -1, -1 };

public:
    monster(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position, const int p_transition_step_size, const int p_current_row, const int p_current_frame, const int p_num_of_frame, const SDL_RendererFlip p_flip);

public:
    void notify_player_moving(const position& p_pos);
};