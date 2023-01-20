#include "dynamic_object_state.h"


std::ostream& operator<<(std::ostream& p_stream, const dynamic_object_state p_state) {
    switch (p_state) {
    case dynamic_object_state::moving_down:
        p_stream << "moving_down";
        break;

    case dynamic_object_state::moving_left:
        p_stream << "moving_left";
        break;

    case dynamic_object_state::moving_right:
        p_stream << "moving_right";
        break;

    case dynamic_object_state::moving_up:
        p_stream << "moving_up";
        break;

    case dynamic_object_state::wait_for_destination:
        p_stream << "wait_for_destination";
        break;

    default:
        p_stream << "unknown";
    }

    return p_stream;
}