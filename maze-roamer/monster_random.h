#pragma once

#include "monster.h"


class monster_random : public monster {
public:
	monster_random(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position, const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
		monster(p_id, p_location, p_texture_manager, p_map, p_logical_position, p_current_row, p_current_frame, p_num_of_frame, p_flip)
	{
		m_current_row = int(rand() % 4) + 1;
		m_num_of_frame = 4;
	}

public:
	void update() override;

protected:
	void handle_wait_for_destination() override;
};
