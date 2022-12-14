#pragma once


enum class monster_state {
    moving_left = 0,
    moving_down,
    moving_right,
    moving_up,
    wait_for_destination
};
