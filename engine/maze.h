#pragma once

#include <list>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "game_status_widget.h"
#include "level.h"
#include "level_matrix.h"
#include "level_stats.h"
#include "monster.h"
#include "player.h"
#include "player_context.h"

#include "core/game_object.h"
#include "core/game_object_interim.h"
#include "core/position.h"
#include "core/texture_manager.h"


class maze {
private:
    static constexpr int OBJECT_SIZE = 32;

private:
    std::vector<std::vector<game_object::ptr>> m_objects_fundamental;
    std::vector<std::vector<game_object::ptr>> m_objects_static_on_map;
    std::list<game_object_interim::ptr> m_objects_static_interim;
    std::shared_ptr<player> m_player;
    std::list<std::shared_ptr<monster>> m_monsters;

    level_matrix m_maze;
    level_matrix m_initial_maze;

    level_stats::ptr m_level_stats;

    game_status_widget::ptr m_status_widget;

    bool m_death_seq;
    SDL_Renderer* m_renderer;
    texture_manager m_texture_manager;
    bool m_is_running = true;

public:
    maze(const level& p_level, const player_context::ptr& p_context);

    ~maze();

    void update();

    void render();

    int get_height() const;

    int get_width() const;

    bool is_running() const;

    player::ptr get_player();

    void inventory_action(const int p_inventory_action_number);

private:
    void initialize(const player_context::ptr& p_context);

    void initialize_texture_manager();

    void render_static_objects();

    void activate_bomb();

    bool check_game_over();

    void render_object(const char p_obj_id, const int p_x, const int p_y);

    void check_collision_with_static_objects();

    void check_win_condition();

    void reinitialize();

    void process_expired_object(game_object_interim::ptr& p_object);

    void process_active_bomb(game_object_interim::ptr& p_object);
};