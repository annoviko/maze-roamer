#pragma once


#include <memory>

#include "core/interim.h"

#include "engine/inventory.h"


using booster_t = interim<int>;


struct booster {
    booster_t m_booster;
    inventory_object_t m_type;
};



class player_context {
public:
    using ptr = std::shared_ptr<player_context>;

private:
    static constexpr int DEFAULT_CASH = 0;
    static constexpr int DEFAULT_NUM_BOMBS = 0;
    static constexpr int DEFAULT_HEALTH = 3;

private:
    int m_cash = DEFAULT_CASH;
    int m_health = DEFAULT_HEALTH;

    booster m_current_booster;
    inventory m_invetory;

public:
    booster_t& get_booster();

    const booster_t& get_booster() const;

    bool is_booster_active(const inventory_object_t p_type);

    void activate_booster(const inventory_object_t p_type, const int p_value, const int p_duration_ms);

    const inventory& get_inventory() const;

    inventory& get_inventory();

    void increase_cash(const int p_cash);

    void decrease_cash(const int p_cash);

    int get_cash() const;

    void increase_amount_bombs();

    void decrease_amount_bombs();

    bool has_bombs() const;

    void increase_amount_speed_boosters();

    void decrease_amount_speed_boosters();

    bool has_speed_boosters();

    void increase_amount_stone_skin_boosters();

    void decrease_amount_stone_skin_boosters();

    bool has_stone_skin_boosters();

    void increase_collectible(const char p_id_obj);

    int get_collectible_amount(const char p_id_obj) const;

    void increase_health();

    void decrease_health();

    int get_health() const;

    bool is_dead() const;
};