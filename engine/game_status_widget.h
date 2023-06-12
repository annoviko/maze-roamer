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
    constexpr static int WIDGET_ROWS = 3;
    constexpr static int WIDGET_COLS = 26;
    constexpr static int FONT_Y_DRIFT = -2;

    constexpr static int PROGRESS_BAR_HEIGHT = 14;
    constexpr static int PROGRESS_BAR_WIDTH = 291;
    constexpr static int PROGRESS_BAR_BORDER_SIZE = 3;
    constexpr static int PROGRESS_BAR_X_OFFSET = 190;

    constexpr static int INVENTORY_SLOTS = 7;
    constexpr static int INVENTORY_X_OFFSET = 600;
    constexpr static int INVENTORY_Y_OFFSET = 36;

    constexpr static int HEALTH_X_OFFSET = 736;

private:
    SDL_Renderer* m_renderer = nullptr;
    const texture_manager& m_texture_manager;

    TTF_Font* m_font = TTF_OpenFont("fonts/the-confession-full-regular.ttf", 28);
    TTF_Font* m_font_inventory = TTF_OpenFont("fonts/the-confession-full-regular.ttf", 12);

    int m_x = 0;
    int m_y = 0;

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
    void show_cash();

    void show_health();

    void show_boost_speed();

    void show_inventory();
};