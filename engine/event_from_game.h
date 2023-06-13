#pragma once


#include <variant>

#include "event_base.h"


class event_grant : public event_base {
public:
    event_grant(const char p_object_id, const int p_amount) :
        event_base(p_object_id, p_amount)
    { }
};


using event_from_game = std::variant <
    event_grant
>;
