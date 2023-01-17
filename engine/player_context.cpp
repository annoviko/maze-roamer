#include "player_context.h"


void player_context::increase_score(const int p_score) {
    m_score += p_score;
}


void player_context::decrease_score(const int p_score) {
    m_score -= p_score;
    if (m_score < 0) {
        m_score = 0;
    }
}


int player_context::get_score() const {
    return m_score;
}


void player_context::increase_health() {
    m_health++;
}


void player_context::decrease_health() {
    if (m_health > 0) {
        m_health--;
    }
}


int player_context::get_health() const {
    return m_health;
}


bool player_context::is_dead() const {
    return m_health == 0;
}
