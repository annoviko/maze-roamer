#include "monster_clever.h"

#include <queue>
#include <iostream>

#include "edge_2d.h"


void monster_clever::update() {
    handle_state();
    m_current_frame = 24 + int((SDL_GetTicks() / 100) % m_num_of_frame);
}


const std::list<position>& monster_clever::get_path() const {
    return m_path_to_player;
}


void monster_clever::handle_wait_for_destination() {
    if (m_path_to_player.empty() || (m_logical_player != m_logical_player_last)) {
        m_path_to_player = calculate_path_to_player();
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
    if (m_state != dynamic_object_state::wait_for_destination) {
        handle_state();
    }
}


std::list<position> monster_clever::calculate_path_to_player() {
    if (m_masters.empty()) {
        return calculate_path_bfs();
    }

    return calculate_path_dijkstra();
}


std::list<position> monster_clever::calculate_path_bfs() const {
    if (m_logical_player == m_logical_location) {
        return { m_logical_player };
    }

    const position not_visited = { -1, -1 };
    const position initial = { 0, 0 };

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

            if (way == m_logical_player) {
                player_found = true;
                break;
            }

            to_process.push(way);
        }
    }

    if (!player_found) {
        throw std::exception("No way to player");
    }

    std::list<position> result;
    for (position p = m_logical_player; p != m_logical_location; p = path_back[p.y][p.x]) {
        result.push_front(p);
    }

    return result;
}


std::list<position> monster_clever::calculate_path_dijkstra() const {
    const position not_visited = { -1, -1 };
    const position initial = { 0, 0 };

    std::vector<std::vector<position>> path_back(m_map->size(), std::vector<position>(m_map->front().size(), not_visited));

    std::vector<std::vector<int>> graph(m_map->size(), std::vector<int>(m_map->front().size(), INT_MAX));
    for (int i = 0; i < m_map->size(); i++) {
        for (int j = 0; j < m_map->front().size(); j++) {
            if ((*m_map)[i][j] != '#') {
                graph[i][j] = 1;
            }
        }
    }

    for (const auto& master : m_masters) {
        for (const auto& pos : master->get_path()) {
            if (pos == m_logical_player) {
                continue; // no fine for player position
            }

            graph[pos.y][pos.x] = 5;
        }
    }

    std::vector<std::vector<int>> cost(m_map->size(), std::vector<int>(m_map->front().size(), INT_MAX));

    std::priority_queue<edge_2d, std::vector<edge_2d>, std::greater<edge_2d>> queue;
    queue.push({ m_logical_location.x, m_logical_location.y, 0 });

    while (!queue.empty()) {
        edge_2d cur = queue.top();
        queue.pop();

        if (cur.weight > cost[cur.y][cur.x]) {
            continue;
        }

        const auto possible_ways = get_possible_steps(cur.x, cur.y);
        for (const auto& way : possible_ways) {
            const int nei_weight = cur.weight + graph[way.y][way.x];
            if (nei_weight < cost[way.y][way.x]) {
                cost[way.y][way.x] = nei_weight;
                queue.push({ way.x, way.y, nei_weight });

                path_back[way.y][way.x] = { cur.x, cur.y };
            }
        }
    }

    std::list<position> result;
    for (position p = m_logical_player; p != m_logical_location; p = path_back[p.y][p.x]) {
        result.push_front(p);
    }

    return result;
}