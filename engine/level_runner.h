#pragma once


#include <SDL.h>

#include "player_context.h"
#include "scenario.h"



class level_runner {
private:
    player_context::ptr m_context;

    bool m_is_running = false;
    bool m_is_pause = false;

public:
    level_runner(const player_context::ptr& p_context);

public:
    void run(const scenario& p_scenario);

    bool is_game_over() const;
};
