#include "maze.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <SDL_image.h>

#include "booster_speed.h"
#include "coin.h"
#include "ground.h"
#include "monster_random.h"
#include "monster_clever.h"
#include "wall.h"


maze::maze(const level& p_level,const player_context::ptr& p_context, SDL_Renderer* p_renderer) :
    m_renderer(p_renderer),
    m_texture_manager(p_renderer),
    m_player_context(p_context)
{
    m_maze = p_level.load();
    m_initial_maze = m_maze;

    initialize_texture_manager();
    m_font = TTF_OpenFont("fonts/Symtext.ttf", 28);

    m_total_coin = 0;
    m_collected_coin = 0;
    m_remaining_coin = 0;
    m_death_seq = false;
}


maze::~maze() {
    m_is_running = false;
    TTF_CloseFont(m_font);
}


void maze::initialize_texture_manager() {
    m_texture_manager.load("img/pacman.png");
}


void maze::initialize() {
    int x = 0, y = 0;

    m_objects_static_on_map = std::vector<std::vector<game_object::ptr>>(m_maze.size(), std::vector<game_object::ptr>(m_maze[0].size(), nullptr));

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
                m_objects_static_on_map[i][j] = std::make_shared<coin>(value, rect, position{ i, j }, m_texture_manager);
                m_total_coin++;
                break;

            case '@':
                m_objects_static_on_map[i][j] = std::make_shared<booster_speed>(value, rect, position{ i, j }, m_texture_manager);
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

    m_remaining_coin = m_total_coin;

    render();
    render_bottom();
}

void maze::check_collision_with_static_objects() {
    auto& static_object = m_objects_static_on_map[m_player->get_logical_location().y][m_player->get_logical_location().x];
    if (static_object != nullptr) {
        switch (static_object->get_id()) {
        case '$':
            m_player_context->increase_score(100);
            m_collected_coin++;

            static_object = nullptr;
            render_bottom();

            m_remaining_coin--;
            check_win_condition();
            break;

        case '@':
            m_player->boost_speed(2, 5000);
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
            if (check_game_over()) {
                return;
            }
        }

        monster_ptr->notify_player_moving(m_player->get_logical_location());
        monster_ptr->update();

        /* check if monster made a step into dynamic object */
        if (monster_ptr->is_collision(*m_player)) {
            if (check_game_over()) {
                return;
            }
        }
    }

    check_collision_with_static_objects();
}


void maze::reinitialize() {
    int x = 0, y = 0;
    m_monsters.clear();
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
                m_monsters.push_back(std::make_shared<monster_clever>('C', rect, m_texture_manager, &m_maze, position{ j, i }));
                break;

            case 'P':
                m_player = std::make_shared<player>('P', rect, m_texture_manager, &m_maze, position{ j, i });
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


void maze::check_win_condition() {
    if (m_remaining_coin == 0) {
        m_is_running = false;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Congratulations!", "Congratulations! You have passed the level!", nullptr);
    }
}


bool maze::check_game_over() {
    m_player_context->decrease_health();
    if (m_player_context->is_dead()) {
        m_is_running = false;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Game Over", nullptr);

        return true;
    }

    m_death_seq = true;
    render_static_objects();
    m_player->render();
    SDL_RenderPresent(m_renderer);
    SDL_Delay(500);
    render_bottom();

    return false;
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
    return static_cast<int>(OBJECT_SIZE * m_maze.size());
}


int maze::get_width() const {
    return static_cast<int>(OBJECT_SIZE * m_maze.front().size());
}

void maze::show_health()
{
    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, "Health:", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 595, 410, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    const int health = m_player_context->get_health();

    SDL_Rect location = { 736, 414, 32, 32 };
    m_texture_manager.draw_frame(location, 10, health < 3, SDL_FLIP_NONE);
    location = { 768, 414, 32,32 };
    m_texture_manager.draw_frame(location, 10, health < 2, SDL_FLIP_NONE);
    location = { 800, 414, 32,32 };
    m_texture_manager.draw_frame(location, 10, health < 1, SDL_FLIP_NONE);
}

void maze::show_score()
{
    //Score: 00000
    std::string message("Score: ");
    const int score = m_player_context->get_score();
    if (score == 0)
    {
        message.append("00000");
    }
    else {
        int cnt = 5 - (int)log10(score);
        while (cnt > 0)
        {
            cnt--;
            message.append("0");
        }
        message.append(std::to_string(score));
    }
    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, message.c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 5, 410, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void maze::render_bottom()
{
    SDL_Rect rect = { 0, 410, 832, 38 };
    SDL_SetRenderDrawColor(m_renderer, 0xff, 0x5b, 0x00, 0xff);
    SDL_RenderFillRect(m_renderer, &rect);

    show_score();
    show_health();
    show_progress();
}

void maze::show_progress() const
{
    SDL_Rect progress = { 278, 425, 291, 14 };
    SDL_Rect border = { progress.x - 3, progress.y - 3, progress.w + 6, progress.h + 6 };
    SDL_SetRenderDrawColor(m_renderer, 0x5a, 0x74, 0x7a, 0xff);
    SDL_RenderFillRect(m_renderer, &border);
    SDL_SetRenderDrawColor(m_renderer, 0x18, 0x37, 0x3d, 0xff);
    SDL_RenderFillRect(m_renderer, &progress);
    double percentage = progress.w * m_collected_coin / (double)m_total_coin;
    SDL_Rect progress_value = { progress.x, progress.y, (int)percentage, progress.h };
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xb6, 0x30, 0xff);
    SDL_RenderFillRect(m_renderer, &progress_value);
}