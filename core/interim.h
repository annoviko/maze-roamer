#pragma once


#include <chrono>
#include <limits>


template <typename ObjectContext>
class interim {
private:
    constexpr static int INVALID_TIME_VALUE = std::numeric_limits<int>::max();

private:
    bool m_active = false;
    int m_duration_ms = 0;
    std::chrono::time_point<std::chrono::system_clock> m_start_time;

    ObjectContext m_value = ObjectContext();

public:
    interim() = default;

public:
    bool is_active() {
        if (m_active) {
            update_state();
        }

        return m_active;
    }

    void activate(const ObjectContext& p_value, const int p_duration_ms) {
        m_active = true;
        m_duration_ms = p_duration_ms;
        m_start_time = std::chrono::system_clock::now();
        m_value = p_value;
    }

    int get_total_duration_time_ms() const {
        return m_duration_ms;
    }

    int get_active_duration_time_ms() const {
        if (!m_active) {
            return INVALID_TIME_VALUE;
        }

        const auto cur_time = std::chrono::system_clock::now();
        const std::chrono::duration<double> duration = cur_time - m_start_time;
        const auto active_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        return static_cast<int>(active_ms);
    }

    int get_remaining_time_ms() const {
        if (!m_active) {
            return 0;
        }

        const auto active_ms = get_active_duration_time_ms();
        return m_duration_ms - active_ms;
    }

private:
    void update_state() {
        const auto duration_ms = get_active_duration_time_ms();
        m_active = (duration_ms < m_duration_ms);
    }
};