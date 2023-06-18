#include "inventory.h"


int inventory::get_amount(const inventory_object_t p_type) const {
    return m_objects[static_cast<int>(p_type)];
}


void inventory::increment(const inventory_object_t p_type, const int p_amount) {
    if (m_objects[static_cast<int>(p_type)] == 0) {
        m_objects_stack.push_back(p_type);
    }

    m_objects[static_cast<int>(p_type)] += p_amount;
}


void inventory::decrement(const inventory_object_t p_type) {
    if (m_objects[static_cast<int>(p_type)] > 0) {
        m_objects[static_cast<int>(p_type)]--;

        if (m_objects[static_cast<int>(p_type)] == 0) {
            auto iter = std::find(m_objects_stack.begin(), m_objects_stack.end(), p_type);
            if (iter != m_objects_stack.end()) {
                m_objects_stack.erase(iter);
            }
        }
    }
}


bool inventory::exists(const inventory_object_t p_type) const {
    return m_objects[static_cast<int>(p_type)] > 0;
}


inventory_object_t inventory::get_object_by_position(const int p_position) const {
    if (p_position >= m_objects_stack.size()) {
        return inventory_object_t::__NULL__;
    }

    int cur_pos = 0;
    for (auto iter = m_objects_stack.begin(); iter != m_objects_stack.end(); iter++, cur_pos++) {
        if (cur_pos == p_position) {
            return *iter;
        }
    }

    return inventory_object_t::__NULL__;
}


std::list<inventory_object_t> inventory::get_objects_as_stack() const {
    return m_objects_stack;
}


int inventory::get_collectible_amount(const char p_obj_id) const {
    auto iter = m_collectible_objects.find(p_obj_id);
    if (iter != m_collectible_objects.end()) {
        return iter->second;
    }

    return 0;
}


void inventory::increment_colletible(const char p_obj_id) {
    m_collectible_objects[p_obj_id]++;
}


void inventory::clean_collectible() {
    m_collectible_objects.clear();
}
