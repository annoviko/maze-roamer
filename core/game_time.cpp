#include "game_time.h"


void game_time::pause() {
    m_is_running = false;
    update_ticks();
}


void game_time::resume() {
    m_is_running = true;
    m_last_measure = std::chrono::system_clock::now();
}


long long game_time::get_ticks() {
    if (m_is_running) {
        update_ticks();
    }

    return m_ticks;
}


void game_time::update_ticks() {
    const auto cur_time = std::chrono::system_clock::now();
    const std::chrono::duration<double> duration = cur_time - m_last_measure;

    m_ticks += std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    m_last_measure = cur_time;
}
