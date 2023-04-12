#pragma once


#include <SDL.h>

#include "level.h"
#include "player_context.h"



class level_runner {
private:
    player_context::ptr m_context;

    bool m_is_running = false;

public:
    level_runner(const player_context::ptr& p_context);

public:
    void run(const level& p_level);

    bool is_game_over() const;
};
