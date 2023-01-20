#pragma once


#include <iostream>


enum class dynamic_object_state {
    moving_left = 0,
    moving_down,
    moving_right,
    moving_up,
    wait_for_destination
};


std::ostream& operator<<(std::ostream& p_stream, const dynamic_object_state p_state);
