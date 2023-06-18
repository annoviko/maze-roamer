#pragma once


#include <queue>

#include "core/singleton.h"

#include "event_from_scenario.h"


class event_pool_from_scenario : public singleton<event_pool_from_scenario> {
private:
    std::queue<event_from_scenario> m_pool;

public:
    void push(const event_from_scenario& p_event);

    event_from_scenario pop();

    bool is_empty() const;

    void clear();
};
