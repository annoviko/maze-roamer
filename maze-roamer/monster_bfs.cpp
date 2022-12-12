#include "monster_bfs.h"

#include <queue>


position monster_bfs::move(const position& p_player) {
    if (p_player == m_current_position) {
        return m_current_position;
    }

    m_prev_player_position = m_cur_player_position;
    m_cur_player_position = p_player;

    handle_state();

    return m_current_position;
}


void monster_bfs::handle_wait_for_input() {
    if (m_cur_player_position != m_prev_player_position) {
        m_path_to_player = get_path_to_player(m_cur_player_position);
    }

    if (!m_path_to_player.empty()) {
        m_prev_position = m_current_position;
        m_next_position = m_path_to_player.front();

        m_path_to_player.pop_front();
    }

    m_state = monster_state::cell_transition;

    handle_transition();
}


std::list<position> monster_bfs::get_path_to_player(const position& p_player) {
    position not_visited = { -1, -1 };
    position initial = { 0, 0 };

    std::vector<std::vector<position>> path_back(m_map->size(), std::vector<position>(m_map->front().size(), not_visited));

    std::queue<position> to_process;
    to_process.push({ m_current_position.x, m_current_position.y });
    path_back[m_current_position.y][m_current_position.x] = initial;

    bool player_found = false;

    while (!to_process.empty() && !player_found) {
        position cur = to_process.front();
        to_process.pop();

        auto possible_ways = get_possible_steps(cur);
        for (const auto& way : possible_ways) {
            if (path_back[way.y][way.x] != not_visited) {
                continue;
            }

            path_back[way.y][way.x] = cur;

            if (way == p_player) {
                player_found = true;
                break;
            }

            to_process.push(way);
        }
    }

    if (!player_found) {
        throw std::exception("No way to player");
    }

    std::list<position> result = { };
    for (position p = p_player; p != m_current_position; p = path_back[p.y][p.x]) {
        result.push_front(p);
    }

    return result;
}