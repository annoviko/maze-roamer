#include "player_context.h"


booster_t& player_context::get_booster() {
    return m_current_booster.m_booster;
}


const booster_t& player_context::get_booster() const {
    return m_current_booster.m_booster;
}


bool player_context::is_booster_active(const inventory_object_t p_type) {
    return (m_current_booster.m_type == p_type) && m_current_booster.m_booster.is_active();
}


void player_context::activate_booster(const inventory_object_t p_type, const int p_value, const int p_duration_ms) {
    if (m_invetory.exists(p_type)) {
        m_current_booster.m_booster.activate(p_value, p_duration_ms);
        m_current_booster.m_type = p_type;
        m_invetory.decrement(p_type);
    }
}


const inventory& player_context::get_inventory() const {
    return m_invetory;
}


inventory& player_context::get_inventory() {
    return m_invetory;
}


void player_context::increase_score(const int p_score) {
    m_score += p_score;
}


void player_context::decrease_score(const int p_score) {
    m_score -= p_score;
    if (m_score < 0) {
        m_score = 0;
    }
}


void player_context::increase_amount_bombs() {
    m_invetory.increment(inventory_object_t::BOMB);
}


void player_context::decrease_amount_bombs() {
    m_invetory.decrement(inventory_object_t::BOMB);
}


bool player_context::has_bombs() const {
    return m_invetory.exists(inventory_object_t::BOMB);
}


void player_context::increase_amount_speed_boosters() {
    m_invetory.increment(inventory_object_t::BOOSTER_SPEED);
}


void player_context::decrease_amount_speed_boosters() {
    m_invetory.decrement(inventory_object_t::BOOSTER_SPEED);
}


bool player_context::has_speed_boosters() {
    return m_invetory.exists(inventory_object_t::BOOSTER_SPEED);
}


void player_context::increase_amount_stone_skin_boosters() {
    m_invetory.increment(inventory_object_t::BOOSTER_STONE_SKIN);
}


void player_context::decrease_amount_stone_skin_boosters() {
    m_invetory.decrement(inventory_object_t::BOOSTER_STONE_SKIN);
}


bool player_context::has_stone_skin_boosters() {
    return m_invetory.exists(inventory_object_t::BOOSTER_STONE_SKIN);
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
