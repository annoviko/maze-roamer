#include "level_stats.h"


level_stats::level_stats(const int p_total_coins) :
    m_total_coins(p_total_coins),
    m_remaining_coins(p_total_coins)
{ }


void level_stats::decrease_remaining_coins() {
    m_remaining_coins--;
}


int level_stats::get_total_coins() const {
    return m_total_coins;
}


int level_stats::get_collected_coins() const {
    return m_total_coins - m_remaining_coins;
}


int level_stats::get_remaining_coins() const {
    return m_remaining_coins;
}
