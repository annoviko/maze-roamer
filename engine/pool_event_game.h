#pragma once


#include <queue>

#include "core/singleton.h"

#include "event_from_game.h"


class pool_event_game : public singleton<pool_event_game> {
private:
    std::queue<event_from_game> m_pool;

public:
    void push(const event_from_game& p_event);

    event_from_game pop();

    bool is_empty() const;

    void clear();
};
