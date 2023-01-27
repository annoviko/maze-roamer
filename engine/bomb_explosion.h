#pragma once


#include <vector>

#include "core/position.h"

#include "level_matrix.h"


class bomb_explosion {
public:
    std::vector<position> boom(const level_matrix& p_maze, const position& p_activation);

private:
    void expand_damage(const level_matrix& p_maze, const position& p_position, const position& p_direction, std::vector<position>& p_damage);
};
