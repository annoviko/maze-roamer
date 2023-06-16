#pragma once


#include <iostream>
#include <string>
#include <vector>

#include "event_from_game.h"
#include "window_image.h"


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

    void play() {
        play_intro();
        play_start_events();
    }


private:
    void play_start_events() { }


    void play_intro() {
        if (m_intro.empty()) {
            std::cout << "The quest does not have intro to play." << std::endl;
            return;
        }

        std::cout << "Play intro '" << m_intro << "' for the quest." << std::endl;
        window_image(m_intro).show();
    }
};
