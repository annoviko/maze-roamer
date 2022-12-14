#pragma once

#include "monster.h"

#include <list>


class monster_clever : public monster {
private:
    std::list<position> m_path_to_player; // cache it
    position m_logical_player_last = { -1, -1 };

public:
    monster_clever(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position) :
        monster(p_id, p_location, p_texture_manager, p_map, p_logical_position)
    { }

public:
    void update() override;

protected:
    void handle_wait_for_destination() override;

private:
    std::list<position> get_path_to_player(const position& p_player);
};
