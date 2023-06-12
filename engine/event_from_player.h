#pragma once


#include <variant>


class event_base {
protected:
    char m_subject_id;

public:
    event_base(const char p_subject_id) :
        m_subject_id(p_subject_id)
    { }

public:
    char get_subject_id() { return m_subject_id; }
};


class event_collect : public event_base {
public:
    event_collect(const char p_object_id) :
        event_base(p_object_id)
    { }
};


class event_kill : public event_base {
public:
    event_kill(const char p_monster_id) :
        event_base(p_monster_id)
    { }
};


class event_reach_checkpoint : public event_base {
public:
    event_reach_checkpoint(const char p_object) :
        event_base(p_object)
    { }
};


using event_from_player = std::variant <
    event_collect,
    event_kill,
    event_reach_checkpoint
>;
