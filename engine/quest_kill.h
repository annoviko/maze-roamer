#pragma once


#include "event_from_player.h"

#include "quest_base.h"


class quest_kill : public quest_base {
private:
    char m_object_id;

    int m_expected = 0;
    int m_current = 0;

public:
    quest_kill(const std::string& p_description, const char p_object_id, const int p_expected, const int p_current) :
        quest_base(p_description),
        m_object_id(p_object_id),
        m_expected(p_expected),
        m_current(p_current)
    { }

public:

    bool handle_event_impl(const event_kill& p_event) {
        std::cout << "Event event_kill '" << p_event.get_subject_id() << "' is received by quest_kill." << std::endl;
        m_current++;

        std::cout << "Quest state. Current: '" << m_current << "', Expected: '" << m_expected << "'." << std::endl;

        if ((m_current >= m_expected) && !is_delay_completion_timer_on()) {
            start_delay_completion_timer();
        }
        return is_done();
    }


    bool handle_event_impl(const event_ping& p_event) {
        return is_done();
    }


    template<typename TypeEvent>
    bool handle_event_impl(const TypeEvent& p_event) {
        return false;
    }


    template<typename TypeEvent>
    bool handle_event(const TypeEvent& p_event) {
        return std::visit([this](const auto& event) -> bool {
            return this->handle_event_impl(event); },
            p_event);
    }

private:
    bool is_done() {
        return (m_current >= m_expected) && is_delay_completion_over();
    }
};
