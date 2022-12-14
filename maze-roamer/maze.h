#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "level_matrix.h"
#include "monster.h"
#include "player.h"

#include "core/game_object.h"
#include "core/position.h"
#include "core/texture_manager.h"


class maze {
private:
    static constexpr int OBJECT_SIZE = 32;

private:
    std::vector<std::vector<game_object::ptr>> m_objects_fundamental;
    std::vector<std::vector<game_object::ptr>> m_objects_static;
    std::shared_ptr<player> m_player;
    std::vector<std::shared_ptr<monster>> m_monsters;

    level_matrix m_maze;

    SDL_Renderer * m_renderer;

    texture_manager m_texture_manager;

    bool m_is_running = true;

public:
    maze(const std::string& p_filepath, SDL_Renderer * p_renderer);

    ~maze();

    void update();

    void render();

    void move_right();

    void move_left();

    void move_up();

    void move_down();

    int get_height() const;

    int get_width() const;

    bool is_running() const;

public:
    void initialize();

private:
    void initialize_texture_manager();

    void render_static_objects();

    void game_over();

    void render_object(const char p_obj_id, const int p_x, const int p_y);
};