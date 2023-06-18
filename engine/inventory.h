#pragma once


#include <list>
#include <vector>
#include <unordered_map>


enum class inventory_object_t {
    BOMB = 0,
    BOOSTER_SPEED,
    BOOSTER_STONE_SKIN,
    __LENGTH__,
    __NULL__
};


class inventory {
private:
    std::vector<int> m_objects = std::vector<int>(static_cast<std::size_t>(inventory_object_t::__LENGTH__));
    std::list<inventory_object_t> m_objects_stack;

    std::unordered_map<char, int> m_collectible_objects;

public:
    int get_amount(const inventory_object_t p_type) const;

    void increment(const inventory_object_t p_type, const int p_amount = 1);

    void decrement(const inventory_object_t p_type);

    bool exists(const inventory_object_t p_type) const;

    inventory_object_t get_object_by_position(const int p_position) const;

    std::list<inventory_object_t> get_objects_as_stack() const;

    int get_collectible_amount(const char p_obj_id) const;

    void increment_colletible(const char p_obj_id);

    void clean_collectible();
};