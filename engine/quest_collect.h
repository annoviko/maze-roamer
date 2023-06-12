#pragma once


#include "event_from_player.h"



class quest_collect {
private:
    char m_object_id;

    int m_expected = 0;
    int m_current = 0;

public:
    quest_collect(const char p_object_id, const int p_expected, const int p_current) :
        m_object_id(p_object_id),
        m_expected(p_expected),
        m_current(p_current)
    { }

public:
    bool handle_event(const event_collect& p_event) {
        return (++m_current >= m_expected);
    }


    template<typename TypeEvent>
    bool handle_event(const TypeEvent& p_event) {
        return false;
    }
};
