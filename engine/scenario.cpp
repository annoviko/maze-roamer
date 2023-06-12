#include "scenario.h"


scenario::scenario(const std::string p_description) :
    m_description(p_description)
{ }


void scenario::play_intro_prompts() {

}


void scenario::play_final_prompts() {
}


void scenario::add_intro_visual_prompt(const std::string& p_path) {
    m_intro_visual_prompts.push_back(p_path);
}


void scenario::add_final_visual_prompt(const std::string& p_path) {
    m_final_visual_prompts.push_back(p_path);
}


void scenario::add_quest_to_collect_items(const std::uint64_t p_obj_id, const int p_amount) {
    m_collections[p_obj_id] = { p_amount, 0 };
}


void scenario::add_quest_to_kill_monsters(const std::uint64_t p_monster_id, const int p_amount) {
    m_kills[p_monster_id] = { p_amount, 0 };
}


const std::string& scenario::get_description() const {
    return m_description;
}


void scenario::increment_collection(const std::uint64_t p_obj_id, const int p_amount) {
    auto& progress = m_collections[p_obj_id];

    progress.m_actual += p_amount;
    if (progress.m_actual >= progress.m_expected) {
        is_done();
    }
}


void scenario::increment_kills(const std::uint64_t p_monster_id, const int p_amount) {
    auto& progress = m_kills[p_monster_id];

    progress.m_actual += p_amount;
    if (progress.m_actual >= progress.m_expected) {
        is_done();
    }
}


bool scenario::is_done() {
    if (!m_scenario_done) {
        play_final_prompts();
        m_scenario_done = true;
    }

    return m_scenario_done;
}
