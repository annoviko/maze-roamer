#pragma once


#include "dynamic_game_object.h"


class player : public dynamic_game_object {
private:
    dynamic_object_state m_last_state = dynamic_object_state::wait_for_destination;

    dynamic_object_state m_next_state = dynamic_object_state::wait_for_destination;

public:
    player(const char p_id, const SDL_Rect& p_location, const texture_manager& p_texture_manager, const level_matrix* p_map, const position p_logical_position) :
        dynamic_game_object(p_id, p_location, p_texture_manager, p_map, p_logical_position)
    { }

public:
    void move_right();

    void move_up();

    void move_left();

    void move_down();

    void update() override;

protected:
    void try_change_destination(const dynamic_object_state p_state);

    void handle_wait_for_destination() override;
};