#pragma once


#include <memory>


class level_stats {
public:
    using ptr = std::shared_ptr<level_stats>;

private:
    int m_total_coins;
    int m_remaining_coins;

public:
    level_stats(const int p_total_coins);

public:
    void decrease_remaining_coins();

    int get_total_coins() const;

    int get_collected_coins() const;

    int get_remaining_coins() const;
};