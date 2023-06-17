#pragma once


#include <iostream>

#include "event_from_player.h"
#include "quest_base.h"


class quest_reach_checkpoint : public quest_base {
private:
    char m_checkpoint_id;

public:
    quest_reach_checkpoint(const std::string& p_description, const char p_checkpoint_id) :
        quest_base(p_description),
        m_checkpoint_id(p_checkpoint_id) 
    { }

public:
    bool handle_event_impl(const event_reach_checkpoint& p_event) {
        std::cout << "Event event_reach_checkpoint '" << p_event.get_subject_id() << "' is received by quest_reach_checkpoint." << std::endl;
        return (m_checkpoint_id == p_event.get_subject_id());
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
