#pragma once


#include <iostream>
#include <string>
#include <vector>

#include "core/game_time.h"

#include "event_from_scenario.h"
#include "event_pool_from_scenario.h"
#include "window_image.h"


class quest_base {
protected:
    std::string m_description;
    std::string m_intro;

    std::uint64_t m_delay_completion = 0;
    std::uint64_t m_delay_time_begin = 0;

    std::vector<event_from_scenario> m_start_events;

public:
    quest_base(const std::string& p_description) :
        m_description(p_description)
    { }

public:
    const std::string& get_description() const {
        return m_description;
    }


    void set_delay_completion(const std::uint32_t delay_ms) {
        m_delay_completion = delay_ms;
    }


    std::uint32_t get_delay_completion() {
        return m_delay_completion;
    }


    void start_delay_completion_timer() {
        m_delay_time_begin = game_time::get().get_ticks();
    }


    bool is_delay_completion_timer_on() {
        return m_delay_time_begin != 0;
    }


    bool is_delay_completion_over() {
        std::uint64_t current_time = game_time::get().get_ticks();
        return (current_time - m_delay_time_begin) > m_delay_completion;
    }


    void add_intro_image(const std::string& p_path) {
        m_intro = p_path;
    }


    void add_start_event(const event_from_scenario& p_event) {
        m_start_events.push_back(p_event);
    }

    void play() {
        play_intro();
        play_start_events();
    }


private:
    void play_start_events() {
        for (auto& cur_event : m_start_events) {
            event_pool_from_scenario::get().push(cur_event);
        }
    }

    void play_intro() {
        if (m_intro.empty()) {
            std::cout << "The quest does not have intro to play." << std::endl;
            return;
        }

        std::cout << "Play intro '" << m_intro << "' for the quest." << std::endl;
        window_image(m_intro).show();
    }
};
