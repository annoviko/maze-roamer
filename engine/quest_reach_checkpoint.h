#pragma once


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
    bool handle_event(const event_collect& p_event) {
        return true;
    }


    template<typename TypeEvent>
    bool handle_event(const TypeEvent& p_event) {
        return false;
    }
};
