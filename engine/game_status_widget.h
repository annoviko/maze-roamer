#pragma once


#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

#include "level_stats.h"
#include "player_context.h"

#include "core/texture_manager.h"


class game_status_widget {
public:
    using ptr = std::shared_ptr<game_status_widget>;

private:
    constexpr static int WIDGET_CELL_SIZE = 32;
    constexpr static int WIDGET_ROWS = 2;
    constexpr static int WIDGET_COLS = 26;

private:
    SDL_Renderer* m_renderer = nullptr;
    const texture_manager& m_texture_manager;

    TTF_Font* m_font = TTF_OpenFont("fonts/Symtext.ttf", 28);

    int m_x = 0;
    int m_y = 0;
    int m_w = 0;
    int m_h = 0;

    level_stats::ptr m_level_stats = nullptr;
    player_context::ptr m_player_context = nullptr;

public:
    game_status_widget() = default;

    game_status_widget(SDL_Renderer * p_renderer, const texture_manager& p_texture_manager, 
        const int p_x, const int p_y, 
        const player_context::ptr & p_context,
        const level_stats::ptr & p_level_stats);

public:
    static int get_height();

    static int get_width();

public:
    void render();

private:
    void show_score();

    void show_health();

    void show_progress();

    void show_boost_speed();
};