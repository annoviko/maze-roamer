#pragma once

#include "monster.h"

#include <list>


class monster_clever : public monster {
public:
    using ptr = std::shared_ptr<monster_clever>;

protected:
    static constexpr int MONSTER_CLEVER_TRANSITION_STEP_SIZE = 1;

private:
    std::list<position> m_path_to_player; // cache it
    position m_logical_player_last = { -1, -1 };

    std::vector<monster_clever::ptr> m_masters;

public:
    monster_clever(const char p_id, 
        const SDL_Rect& p_location, 
        const texture_manager& p_texture_manager, 
        const level_matrix* p_map, 
        const position p_logical_position, 
        const std::vector<monster_clever::ptr>& p_masters = { },
        const int p_current_row = 1, const int p_current_frame = 0, const int p_num_of_frame = 0, 
        const SDL_RendererFlip p_flip = SDL_FLIP_NONE) :
            monster(p_id, p_location, p_texture_manager, p_map, p_logical_position, MONSTER_CLEVER_TRANSITION_STEP_SIZE, p_current_row, p_current_frame, p_num_of_frame, p_flip),
            m_masters(p_masters)
    {
        m_current_row = int(rand() % 4)+1;
        m_current_frame = 25;
        m_num_of_frame = 4;
    }

public:
    void update() override;

    const std::list<position>& get_path() const;

protected:
    void handle_wait_for_destination() override;

private:
    std::list<position> calculate_path_to_player();

    std::list<position> calculate_path_bfs() const;

    std::list<position> calculate_path_dijkstra() const;
};
