#include "inventory.h"


int inventory::get_amount(const inventory_object_t p_type) const {
    return m_objects[static_cast<int>(p_type)];
}


void inventory::increment(const inventory_object_t p_type) {
    if (m_objects[static_cast<int>(p_type)] == 0) {
        m_objects_stack.push_back(p_type);
    }

    m_objects[static_cast<int>(p_type)]++;
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
    int cur_pos = 0;
    for (int i = 0; i < static_cast<int>(inventory_object_t::__LENGTH__); i++) {
        if (m_objects[i] > 0) {
            if (cur_pos == p_position) {
                return static_cast<inventory_object_t>(m_objects[i]);
            }

            cur_pos++;
        }
    }

    return inventory_object_t::__NULL__;
}


std::list<inventory_object_t> inventory::get_objects_as_stack() const {
    return m_objects_stack;
}
