#pragma once

#include "core/game_object.h"


class wall : public game_object { 
public:
    wall(const char p_id, const SDL_Rect& p_location, const texture_manager& p_manager) :
        game_object(p_id, p_location, p_manager)
    { }

public:
    void update() { }
};