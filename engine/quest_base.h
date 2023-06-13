#pragma once


#include <string>
#include <vector>

#include "event_from_game.h"


class quest_base {
protected:
    std::string m_description;
    std::string m_intro;

    std::vector<event_from_game> m_start_events;

public:
    quest_base(const std::string& p_description) :
        m_description(p_description)
    { }

public:
    const std::string& get_description() const {
        return m_description;
    }


    void add_intro_image(const std::string& p_path) {
        m_intro = p_path;
    }


    void add_start_event(const event_from_game& p_event) {
        m_start_events.push_back(p_event);
    }

    void play() { }


private:
    void play_start_events() { }


    void play_into() { }
};
