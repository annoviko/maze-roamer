#include "scenario.h"

#include <fstream>

#include <nlohmann/json.hpp>

#include "level.h"


scenario::scenario(const std::string& p_json_path) {
    std::ifstream file_handle(p_json_path);
    nlohmann::json json_scenario = nlohmann::json::parse(file_handle);

    std::string map_path = json_scenario["map"];
    m_maze = level(map_path).load();

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
            std::visit([&map_path](auto&& current_quest) {
                current_quest.add_intro_image(map_path);
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


void scenario::play() {
    
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
}


const level_matrix& scenario::get_maze() const {
    return m_maze;
}


bool scenario::is_done() const {
    return m_is_done;
}
