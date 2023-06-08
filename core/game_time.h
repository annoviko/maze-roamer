#pragma once

#include <chrono>

#include "singleton.h"


class game_time : public singleton<game_time> {
private:
    bool m_is_running = true;
    long long m_ticks = 0;
    std::chrono::time_point<std::chrono::system_clock> m_last_measure = std::chrono::system_clock::now();

public:
    void pause();

    void resume();

    long long get_ticks();

private:
    void update_ticks();
};
