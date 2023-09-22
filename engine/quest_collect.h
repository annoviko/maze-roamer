#pragma once


#include "event_from_player.h"

#include <iostream>

#include "quest_base.h"


class quest_collect : public quest_base {
private:
    char m_object_id;

    int m_expected = 0;
    int m_current = 0;

public:
    quest_collect(const std::string& p_description, const char p_object_id, const int p_expected, const int p_current) :
        quest_base(p_description),
        m_object_id(p_object_id),
        m_expected(p_expected),
        m_current(p_current)
    { }

private:
    bool handle_event_impl(const event_collect& p_event) {
        std::cout << "Event 'event_collect' is received (current: '" << m_current + 1 << "', expected: '" << m_expected << "', remain: '" << p_event.get_remain_amount() << "')." << std::endl;

        m_current++;
        if (m_expected == -1) {
            return (p_event.get_remain_amount() == 0);
        }

        return (m_current >= m_expected);
    }


    template<typename TypeEvent>
    bool handle_event_impl(const TypeEvent& p_event) {
        return false;
    }

public:
    template<typename TypeEvent>
    bool handle_event(const TypeEvent& p_event) {
        return std::visit([this](const auto& event) -> bool { 
            return this->handle_event_impl(event); }, 
        p_event);
    }
};
