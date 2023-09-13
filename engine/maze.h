#pragma once

#include <list>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "game_status_widget.h"
#include "event_from_scenario.h"
#include "level_matrix.h"
#include "monster.h"
#include "player.h"
#include "player_context.h"
#include "scenario.h"

#include "core/game_object.h"
#include "core/game_object_interim.h"
#include "core/position.h"
#include "core/texture_manager.h"


class maze {
private:
    static constexpr int OBJECT_SIZE = 32;

    struct object_stats_entry {
        int total = 0;
        int remain = 0;
    };

private:
    std::vector<std::vector<game_object::ptr>> m_objects_fundamental;
    std::vector<std::vector<game_object::ptr>> m_objects_static_on_map;
    std::list<game_object_interim::ptr> m_objects_static_interim;
    game_object::ptr m_portal = nullptr;
    std::shared_ptr<player> m_player = nullptr;
    std::list<std::shared_ptr<monster>> m_monsters;

    scenario m_scenario;
    level_matrix m_maze;
    level_matrix m_initial_maze;

    game_status_widget::ptr m_status_widget;

    std::unordered_map<char, object_stats_entry> m_object_stats;

    bool m_death_seq;
    SDL_Renderer* m_renderer;
    texture_manager m_texture_manager;
    bool m_is_running = true;

public:
    maze(const scenario& p_scenario, const player_context::ptr& p_context);

    ~maze();

    void run();

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

    int count_remaining_monsters();

    void reinitialize();

    void process_expired_object(game_object_interim::ptr& p_object);

    void process_active_bomb(game_object_interim::ptr& p_object);

    void process_event_pool_from_scenario();

    void handle_event_from_scenario(const event_grant& p_event);

    template<typename TypeEvent>
    void handle_event_from_scenario(const TypeEvent& p_event) { }
};