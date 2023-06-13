#pragma once


#include <variant>

#include "event_base.h"


class event_collect : public event_base {
public:
    event_collect(const char p_object_id, const int p_amount) :
        event_base(p_object_id, p_amount)
    { }
};


class event_kill : public event_base {
public:
    event_kill(const char p_monster_id, const int p_amount) :
        event_base(p_monster_id, p_amount)
    { }
};


class event_reach_checkpoint : public event_base {
public:
    event_reach_checkpoint(const char p_object) :
        event_base(p_object, 1)
    { }
};


using event_from_player = std::variant <
    event_collect,
    event_kill,
    event_reach_checkpoint
>;
