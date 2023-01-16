#pragma once


#include <SDL.h>

#include "level.h"
#include "player_context.h"



class level_runner {
private:
    SDL_Renderer* m_renderer;
    player_context::ptr m_context;

public:
    level_runner(SDL_Renderer* p_renderer, const player_context::ptr& p_context);

public:
    void run(const level& p_level);

    bool is_game_over() const;
};
