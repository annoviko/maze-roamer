#pragma once

#include "monster.h"


class monster_random : public monster {
public:
    monster_random(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position) :
        monster(p_id, p_location, p_texture_manager, p_map, p_logical_position)
    { }

public:
    void update() override;

protected:
    void handle_wait_for_destination() override;
};
