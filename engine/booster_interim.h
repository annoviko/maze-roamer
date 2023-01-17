#pragma once


#include <chrono>


template <typename BoosterContext>
class booster_interim {
private:
    bool m_active = false;
    double m_duration_ms = 0;
    std::chrono::time_point<std::chrono::system_clock> m_start_time;

    BoosterContext m_value = BoosterContext();

public:
    booster_interim() = default;

public:
    bool is_active() {
        if (m_active) {
            update_state();
        }

        return m_active;
    }

    void activate(const BoosterContext& p_value, const int p_duration_ms) {
        m_active = true;
        m_duration_ms = p_duration_ms;
        m_start_time = std::chrono::system_clock::now();
        m_value = p_value;
    }

private:
    void update_state() {
        const auto cur_time = std::chrono::system_clock::now();
        const std::chrono::duration<double> duration = cur_time - m_start_time;
        const auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        m_active = (duration_ms < m_duration_ms);
    }
};