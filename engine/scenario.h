#pragma once


#include <memory>
#include <string>
#include <unordered_map>


class scenario {
public:
    using ptr = std::shared_ptr<scenario>;

private:
    struct progress_entry {
        int m_expected = 0;
        int m_actual = 0;
    };

private:
    std::string m_description;

    std::vector<std::string> m_intro_visual_prompts;  /* contains path */
    std::vector<std::string> m_final_visual_prompts;

    /* try to keep it simple despite this structure, it is better to have a lot of small tasks for player than one big */
    std::unordered_map<std::uint64_t, progress_entry> m_collections;
    std::unordered_map<std::uint64_t, progress_entry> m_kills;

    bool m_scenario_done = false;

public:
    scenario(const std::string p_description);

    ~scenario() = default;

public:
    void play_intro_prompts();

    void play_final_prompts();

    void add_intro_visual_prompt(const std::string& p_path);

    void add_final_visual_prompt(const std::string& p_path);

    void add_quest_to_collect_items(const std::uint64_t p_obj_id, const int p_amount);

    void add_quest_to_kill_monsters(const std::uint64_t p_monster_id, const int p_amount);

    const std::string& get_description() const;

    void increment_collection(const std::uint64_t p_obj_id, const int p_amount = 1);

    void increment_kills(const std::uint64_t p_monster_id, const int p_amount = 1);

    bool is_done();
};