#pragma once


#include <memory>

#include "booster_interim.h"


using speed_booster = booster_interim<int>;


class player_context {
public:
    using ptr = std::shared_ptr<player_context>;

private:
    static constexpr int DEFAULT_SCORE = 0;
    static constexpr int DEFAULT_HEALTH = 3;

private:
    int m_score = DEFAULT_SCORE;
    int m_health = DEFAULT_HEALTH;

    speed_booster m_speed_booster;

public:
    speed_booster& get_speed_booster();

    const speed_booster& get_speed_booster() const;

    void increase_score(const int p_score);

    void decrease_score(const int p_score);

    int get_score() const;

    void increase_health();

    void decrease_health();

    int get_health() const;

    bool is_dead() const;
};