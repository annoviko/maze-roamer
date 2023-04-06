#include "bomb_explosion.h"
#include "object_identifier.h"


std::vector<position> bomb_explosion::boom(const level_matrix& p_maze, const position& p_activation) {
    std::vector<position> damage;

    damage.push_back(p_activation);
    expand_damage(p_maze, p_activation, { -1, 0 }, damage);
    expand_damage(p_maze, p_activation, { 1, 0 }, damage);
    expand_damage(p_maze, p_activation, { 0, -1 }, damage);
    expand_damage(p_maze, p_activation, { 0, 1 }, damage);

    return damage;
}


void bomb_explosion::expand_damage(const level_matrix& p_maze, const position& p_position, const position& p_direction, std::vector<position>& p_damage) {
    position cur = p_position + p_direction;
    while (!object_identifier::is_hurdle(p_maze[cur.y][cur.x])) {
        p_damage.push_back(cur);
        cur += p_direction;
    }
}
