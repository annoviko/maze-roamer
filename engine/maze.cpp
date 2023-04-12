#include "maze.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <SDL_image.h>

#include "core/graphic_context.h"

#include "booster_speed.h"
#include "bomb.h"
#include "bomb_active.h"
#include "bomb_explosion.h"
#include "boom.h"
#include "coin.h"
#include "ground.h"
#include "monster_random.h"
#include "monster_clever.h"
#include "object_identifier.h"
#include "tree.h"
#include "wall.h"
#include "window_game_over.h"
#include "window_win.h"


maze::maze(const level& p_level, const player_context::ptr& p_context) :
    m_renderer(graphic_context::get().get_render()),
    m_texture_manager(graphic_context::get().get_render())
{
    m_maze = p_level.load();
    m_initial_maze = m_maze;

    initialize_texture_manager();

    m_death_seq = false;
    initialize(p_context);
}


maze::~maze() {
    m_is_running = false;
}


void maze::initialize_texture_manager() {
    m_texture_manager.load("img/pacman.png");
}


void maze::initialize(const player_context::ptr& p_context) {
    int x = 0, y = 0;
    int total_coins = 0;

    m_objects_static_on_map = std::vector<std::vector<game_object::ptr>>(m_maze.size(), std::vector<game_object::ptr>(m_maze[0].size(), nullptr));

    std::vector<monster_clever::ptr> clever_masters = { };

    for (int i = 0; i < m_maze.size(); i++) {
        m_objects_fundamental.push_back(std::vector<game_object::ptr>());

        for (int j = 0; j < m_maze[0].size(); j++) {
            auto& value = m_maze[i][j];

            SDL_Rect rect{ x, y, OBJECT_SIZE, OBJECT_SIZE };

            x += OBJECT_SIZE;

            if (!object_identifier::is_hurdle(value)) {
                m_objects_fundamental.back().push_back(std::make_shared<ground>(' ', rect, m_texture_manager));
            }

            switch (value) {
            case 'S':
                m_monsters.push_back(std::make_shared<monster_random>('S', rect, m_texture_manager, &m_maze, position{ j, i }));
                break;

            case 'C':
                clever_masters.push_back(std::make_shared<monster_clever>('C', rect, m_texture_manager, &m_maze, position{ j, i }, clever_masters));
                m_monsters.push_back(clever_masters.back());
                break;

            case 'P':
                m_player = std::make_shared<player>('P', rect, m_texture_manager, p_context, &m_maze, position{ j, i });
                break;

            case '$':
                m_objects_static_on_map[i][j] = std::make_shared<coin>(value, rect, position{ i, j }, m_texture_manager);
                total_coins++;
                break;

            case '@':
                m_objects_static_on_map[i][j] = std::make_shared<booster_speed>(value, rect, position{ i, j }, m_texture_manager);
                break;

            case '!':
                m_objects_static_on_map[i][j] = std::make_shared<bomb>(value, rect, position{ i, j }, m_texture_manager);
                break;

            case '*':
                m_objects_fundamental.back().push_back(std::make_shared<wall>(value, rect, m_texture_manager));
                break;

            case '^':
                m_objects_fundamental.back().push_back(std::make_shared<tree>(value, rect, m_texture_manager));
                break;
            }

            if (!object_identifier::is_hurdle(value) && value != ' ') {
                value = ' '; // clean dynamic objects.
            }
        }

        x = 0;
        y += OBJECT_SIZE;
    }

    m_level_stats = std::make_shared<level_stats>(total_coins);
    m_status_widget = std::make_shared<game_status_widget>(m_renderer, m_texture_manager, 0, (int) m_maze.size() * OBJECT_SIZE, p_context, m_level_stats);
}

void maze::check_collision_with_static_objects() {
    auto& static_object = m_objects_static_on_map[m_player->get_logical_location().y][m_player->get_logical_location().x];
    if (static_object != nullptr) {
        switch (static_object->get_id()) {
        case '$':
            m_player->get_context()->increase_score(100);
            m_level_stats->decrease_remaining_coins();

            static_object = nullptr;
            m_status_widget->render();

            check_win_condition();
            break;

        case '@':
            m_player->boost_speed(2, 5000);
            static_object = nullptr;
            break;

        case '!':
            m_player->get_context()->increase_amount_bombs();
            static_object = nullptr;
            break;
        }
    }
}


void maze::update() {
    if (m_death_seq) {
        return;
    }

    m_player->update();

    for (auto& monster_ptr : m_monsters) {
        /* check if player made a step into dynamic object */
        if (m_player->is_collision(*monster_ptr)) {
            m_player->get_context()->decrease_health();
            check_game_over();
            return;
        }

        monster_ptr->notify_player_moving(m_player->get_logical_location());
        monster_ptr->update();

        /* check if monster made a step into dynamic object */
        if (monster_ptr->is_collision(*m_player)) {
            m_player->get_context()->decrease_health();
            check_game_over();
            return;
        }
    }

    check_collision_with_static_objects();

    for (auto iter = std::begin(m_objects_static_interim); iter != std::end(m_objects_static_interim);) {
        (*iter)->update();

        if ((*iter)->is_expired()) {
            process_expired_object((*iter));
            iter = m_objects_static_interim.erase(iter);
        }
        else {
            iter++;
        }
    }
}


void maze::process_expired_object(game_object_interim::ptr& p_object) {
    switch (p_object->get_id()) {
    case '!':
        process_active_bomb(p_object);
        break;

    case 'B':
    default:
        break;
    }
}


void maze::process_active_bomb(game_object_interim::ptr& p_object) {
    const auto boom_area = bomb_explosion().boom(m_maze, p_object->get_logical_location());
    for (const auto& boom_position : boom_area) {
        if (m_player->is_collision(boom_position)) {
            m_player->get_context()->decrease_health();
            check_game_over();
            return;
        }

        for (auto iter = m_monsters.begin(); iter != m_monsters.end();) {
            const auto& monster = (*iter);
            if (monster->is_collision(boom_position)) {
                iter = m_monsters.erase(iter);
            }
            else {
                iter++;
            }
        }

        SDL_Rect location = { boom_position.x * OBJECT_SIZE, boom_position.y * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE };
        m_objects_static_interim.push_back(std::make_shared<boom>('B', location, boom_position, m_texture_manager));
    }
}


void maze::reinitialize() {
    int x = 0, y = 0;
    m_monsters.clear();

    std::vector<monster_clever::ptr> clever_masters = { };

    for (int i = 0; i < m_initial_maze.size(); i++) {

        for (int j = 0; j < m_initial_maze[0].size(); j++) {
            auto& value = m_initial_maze[i][j];

            SDL_Rect rect{ x, y, OBJECT_SIZE, OBJECT_SIZE };

            x += OBJECT_SIZE;

            switch (value) {
            case 'S':
                m_monsters.push_back(std::make_shared<monster_random>('S', rect, m_texture_manager, &m_maze, position{ j, i }));
                break;

            case 'C':
                clever_masters.push_back(std::make_shared<monster_clever>('C', rect, m_texture_manager, &m_maze, position{ j, i }, clever_masters));
                m_monsters.push_back(clever_masters.back());
                break;

            case 'P':
                m_player = std::make_shared<player>('P', rect, m_texture_manager, m_player->get_context(), &m_maze, position{ j, i });
                break;
            }
        }

        x = 0;
        y += OBJECT_SIZE;
    }
}


void maze::render() {
    if (m_death_seq) {
        SDL_Delay(100);
        render_static_objects();
        m_death_seq = m_player->death();
        m_player->render();
        if (!m_death_seq) {
            reinitialize();
        }
    }
    else {
        render_static_objects();

        m_player->render();

        for (const auto& monster_ptr : m_monsters) {
            monster_ptr->render();
        }
    }

    m_status_widget->render();
    SDL_RenderPresent(m_renderer);
}


void maze::render_static_objects() {
    int x = 0, y = 0;

    for (int i = 0; i < m_objects_fundamental.size(); i++) {
        for (int j = 0; j < m_objects_fundamental[i].size(); j++) {
            auto& object_fundamental = m_objects_fundamental[i][j];
            object_fundamental->render();

            auto& object_static = m_objects_static_on_map[i][j];
            if (object_static != nullptr) {
                object_static->render();
            }
        }

        x = 0;
        y += OBJECT_SIZE;
    }

    for (const auto& temp_static_object : m_objects_static_interim) {
        temp_static_object->render();
    }
}


void maze::render_object(const char p_obj_id, const int p_x, const int p_y) {
    SDL_Rect rect{ p_x, p_y, OBJECT_SIZE, OBJECT_SIZE };

    switch (p_obj_id) {
        case 'P': {
            m_texture_manager.draw(rect);
            break;
        }
    }
}


bool maze::is_running() const {
    return m_is_running;
}


player::ptr maze::get_player() {
    return m_player;
}


void maze::activate_bomb() {
    if (m_player->get_context()->has_bombs()) {
        m_player->get_context()->decrease_amount_bombs();

        const int x = (int) std::round(((double) m_player->get_location().x) / (double) OBJECT_SIZE);
        const int y = (int) std::round(((double) m_player->get_location().y) / (double) OBJECT_SIZE);

        SDL_Rect location{ x * OBJECT_SIZE, y * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE };
        m_objects_static_interim.push_back(std::make_shared<bomb_active>('!', location, position{ x, y }, m_texture_manager));
    }
}


void maze::check_win_condition() {
    if (m_level_stats->get_remaining_coins() == 0) {
        m_is_running = false;
        window_win().show();
    }
}


bool maze::check_game_over() {
    if (m_player->get_context()->is_dead()) {
        m_is_running = false;
        window_game_over().show();

        return true;
    }

    m_death_seq = true;
    render_static_objects();
    m_player->render();
    SDL_RenderPresent(m_renderer);
    SDL_Delay(500);
    m_status_widget->render();

    return false;
}


int maze::get_height() const {
    return static_cast<int>(OBJECT_SIZE * m_maze.size());
}


int maze::get_width() const {
    return static_cast<int>(OBJECT_SIZE * m_maze.front().size());
}
