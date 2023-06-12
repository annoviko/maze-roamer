#pragma once


class quest_reach_checkpoint {
private:
    char m_checkpoint_id;

public:
    quest_reach_checkpoint(const char p_checkpoint_id) :
        m_checkpoint_id(p_checkpoint_id) 
    { }

private:
    bool handle_event(const event_collect& p_event) {
        return true;
    }


    template<typename TypeEvent>
    bool handle_event(const TypeEvent& p_event) {
        return false;
    }
};
