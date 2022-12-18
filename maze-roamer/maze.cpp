#include "maze.h"

#include <fstream>
#include <memory>

#include <SDL_image.h>

#include "coin.h"
#include "ground.h"
#include "monster_random.h"
#include "monster_clever.h"
#include "wall.h"


maze::maze(const std::string& p_filepath, SDL_Renderer* p_renderer, SDL_Window* p_window) :
    m_renderer(p_renderer),
    m_texture_manager(p_renderer),
    m_window(p_window)
{
    std::ifstream stream(p_filepath);

    int row = 0;
    for (std::string line; std::getline(stream, line); ) {
        m_maze.push_back(line);
    }

    initialize_texture_manager();
}


maze::~maze() {
    m_is_running = false;
}


void maze::initialize_texture_manager() {
    m_texture_manager.load("img/pacman.png");
}


void maze::initialize() {
    int x = 0, y = 0;

    m_objects_static = std::vector<std::vector<game_object::ptr>>(m_maze.size(), std::vector<game_object::ptr>(m_maze[0].size(), nullptr));

    for (int i = 0; i < m_maze.size(); i++) {
        m_objects_fundamental.push_back(std::vector<game_object::ptr>());

        for (int j = 0; j < m_maze[0].size(); j++) {
            auto& value = m_maze[i][j];

            SDL_Rect rect{ x, y, OBJECT_SIZE, OBJECT_SIZE };

            x += OBJECT_SIZE;

            if (value != '*') {
                m_objects_fundamental.back().push_back(std::make_shared<ground>(' ', rect, m_texture_manager));
            }

            switch (value) {
            case 'S':
                m_monsters.push_back(std::make_shared<monster_random>('S', rect, m_texture_manager, &m_maze, position{ j, i }));
                break;

            case 'C':
                m_monsters.push_back(std::make_shared<monster_clever>('C', rect, m_texture_manager, &m_maze, position{ j, i }));
                break;

            case 'P':
                m_player = std::make_shared<player>('P', rect, m_texture_manager, &m_maze, position{ j, i });
                break;

            case '$':
                m_objects_static[i][j] = std::make_shared<coin>(value, rect, m_texture_manager);
                break;

            case '*':
                m_objects_fundamental.back().push_back(std::make_shared<wall>(value, rect, m_texture_manager));
                break;
            }

            if (value != '*' && value != ' ') {
                value = ' '; // clean dynamic objects.
            }
        }

        x = 0;
        y += OBJECT_SIZE;
    }

    render();
}

void maze::check_score() {
    auto& static_object = m_objects_static[m_player->get_logical_location().y][m_player->get_logical_location().x];
    if ((static_object != nullptr) && (static_object->get_id() == '$')) {
        m_score += 100;
        static_object = nullptr;
        std::string title("Maze Roamer | Score: ");
        title.append(std::to_string(m_score));
        SDL_SetWindowTitle(m_window, title.c_str());
    }
}

void maze::update() {
    m_player->update();

    for (auto& monster_ptr : m_monsters) {
        monster_ptr->notify_player_moving(m_player->get_logical_location());
        monster_ptr->update();

        if (monster_ptr->get_logical_location() == m_player->get_logical_location()) {
            game_over();
        }
    }
    check_score();
}


void maze::render() {
    render_static_objects();

    m_player->render();

    for (const auto& monster_ptr : m_monsters) {
        monster_ptr->render();
    }

    SDL_RenderPresent(m_renderer);
}


void maze::render_static_objects() {
    int x = 0, y = 0;

    for (int i = 0; i < m_objects_fundamental.size(); i++) {
        for (int j = 0; j < m_objects_fundamental[i].size(); j++) {
            auto& object_fundamental = m_objects_fundamental[i][j];
            object_fundamental->render();

            auto& object_static = m_objects_static[i][j];
            if (object_static != nullptr) {
                object_static->render();
            }
        }

        x = 0;
        y += OBJECT_SIZE;
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


void maze::game_over() {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Game Over", nullptr);
    m_is_running = false;
}


void maze::move_right() {
    m_player->move_right();
}


void maze::move_left() {
    m_player->move_left();
}


void maze::move_up() {
    m_player->move_up();
}


void maze::move_down() {
    m_player->move_down();
}



int maze::get_height() const {
    return OBJECT_SIZE * m_maze.size();
}


int maze::get_width() const {
    return OBJECT_SIZE * m_maze.front().size();
}
