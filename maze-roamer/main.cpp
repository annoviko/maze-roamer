#include <iostream>

#include "core/graphic_context.h"

#include "engine/level_finder.h"
#include "engine/level_runner.h"
#include "engine/player_context.h"


int main(int argc, char* argv[]) {
    graphic_context::get().intialize("Maze Roamer");

    level_finder finder(".");
    player_context::ptr context = std::make_shared<player_context>();

    level_runner runner(context);
    for (std::size_t i = 0; (i < finder.get_levels().size()) && !runner.is_game_over(); i++) {
        runner.run(finder.get_levels()[i]);
    }

    return 0;
}