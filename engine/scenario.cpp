#include "scenario.h"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>


scenario::scenario(const std::string& p_json_path) {
    std::ifstream file_handle(p_json_path);
    nlohmann::json json_scenario = nlohmann::json::parse(file_handle);

    std::string map_path = json_scenario["map"];
    m_maze = load_map(map_path);

    m_epilogue_image = json_scenario["epilogue"];


    for (const auto& json_quest : json_scenario["scenario"]) {
        std::string description = json_quest["description"];

        std::string intro_image = std::string();
        if (json_quest.contains("intro")) {
            intro_image = json_quest["intro"]["image"];
        }

        const auto& json_quest_body = json_quest["quest"];
        std::string quest_type = json_quest_body["type"];
        std::string subject_id = json_quest_body["object-id"];

        if (quest_type == "collect") {
            int amount = json_quest_body["number"];
            m_quests.push_back(quest_collect(description, subject_id[0], amount, 0));
        }
        else if (quest_type == "kill") {
            int amount = json_quest_body["number"];
            m_quests.push_back(quest_kill(description, subject_id[0], amount, 0));
        }
        else if (quest_type == "reach") {
            m_quests.push_back(quest_reach_checkpoint(description, subject_id[0]));
        }

        if (!intro_image.empty()) {
            std::visit([&intro_image](auto&& current_quest) {
                current_quest.add_intro_image(intro_image);
            }, m_quests.back());
        }

        if (json_quest.contains("event-before")) {
            for (const auto& json_event : json_quest["event-before"]) {
                std::string event_type = json_event["type"];

                if (event_type == "grant") {
                    std::string grant_object_id = json_event["object-id"];
                    int amount = json_event["number"];

                    event_grant event_before(grant_object_id[0], amount);
                    std::visit([&event_before](auto&& current_quest) {
                        current_quest.add_start_event(event_before);
                    }, m_quests.back());
                }
            }
        }
    }
}


void scenario::run() {
    if (m_quests.empty()) {
        std::cout << "[ERROR] Impossible to run scenario - no quests to play." << std::endl;

        m_is_done = true;
        return; /* nothing to play - all quests is over */
    }

    std::visit([](auto& current_quest) {
        current_quest.play();
    }, m_quests.front());
}


void scenario::update(const event_from_player& p_event) {
    if (m_quests.empty() || m_is_done) {
        return;
    }

    bool is_quest_done = std::visit([&p_event](auto& current_quest) -> bool {
        return current_quest.handle_event(p_event);
    }, m_quests.front());

    if (!is_quest_done) {
        return;
    }

    std::cout << "Quest is done" << std::endl;

    m_quests.pop_front();
    m_is_done = m_quests.empty();

    if (m_is_done) {
        play_epilogue();
    }
    else {
        std::visit([](auto& current_quest) {
            current_quest.play();
        }, m_quests.front());
    }
}


void scenario::play_epilogue() {
    std::cout << "Play epilogue '" << m_epilogue_image << "'" << std::endl;
    window_image(m_epilogue_image).show();
}


const level_matrix& scenario::get_map() const {
    return m_maze;
}


bool scenario::is_done() const {
    return m_is_done;
}


level_matrix scenario::load_map(const std::string& p_path) {
    std::ifstream stream(p_path);

    level_matrix matrix;

    for (std::string line; std::getline(stream, line); ) {
        matrix.push_back(line);
    }

    return matrix;
}
