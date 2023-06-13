#pragma once


#include <list>
#include <memory>
#include <string>
#include <unordered_map>

#include "level_matrix.h"
#include "quest.h"


class scenario {
private:
    std::list<quest> m_quests;

    level_matrix m_maze;

    std::string m_epilogue_image;

    bool m_is_done = false;

public:
    scenario(const std::string& p_json_path);

public:
    void play();

    void play_epilogue();

    void update(const event_from_player& p_event);

    const level_matrix& get_maze() const;

    bool is_done() const;
};