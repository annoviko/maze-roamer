#include "monster_clever.h"

#include <queue>

#include <iostream>


void monster_clever::update() {
    handle_state();
}


void monster_clever::handle_wait_for_destination() {
    if (m_path_to_player.empty() || (m_logical_player != m_logical_player_last)) {
        m_path_to_player = get_path_to_player(m_logical_player);
        m_logical_player_last = m_logical_player;
    }

    if (!m_path_to_player.empty()) {
        m_logical_destination = m_path_to_player.front();
        m_path_to_player.pop_front();

        m_destination.x = m_logical_destination.x * m_destination.w;
        m_destination.y = m_logical_destination.y * m_destination.h;
    }
    else {
        std::cout << "Clever monster does not where to go!" << std::endl;
    }

    define_moving_state();
    if (m_state != monster_state::wait_for_destination) {
        handle_state();
    }
}


std::list<position> monster_clever::get_path_to_player(const position& p_player) {
    position not_visited = { -1, -1 };
    position initial = { 0, 0 };

    std::vector<std::vector<position>> path_back(m_map->size(), std::vector<position>(m_map->front().size(), not_visited));

    std::queue<position> to_process;
    to_process.push({ m_logical_location.x, m_logical_location.y });
    path_back[m_logical_location.y][m_logical_location.x] = initial;

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
    for (position p = p_player; p != m_logical_location; p = path_back[p.y][p.x]) {
        result.push_front(p);
    }

    return result;
}