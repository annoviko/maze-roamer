#pragma once


#include <variant>

#include "event_base.h"


class event_collect : public event_base {
private:
    int m_remain_amount;

public:
    event_collect(const char p_object_id, const int p_amount, const int p_remain_amount) :
        event_base(p_object_id, p_amount),
        m_remain_amount(p_remain_amount)
    { }

public:
    int get_remain_amount() const {
        return m_remain_amount;
    }
};


class event_kill : public event_collect {
public:
    event_kill(const char p_monster_id, const int p_amount, const int p_remain_amount) :
        event_collect(p_monster_id, p_amount, p_remain_amount)
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
