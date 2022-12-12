#pragma once

#include <type_traits>


struct position {
    int x = 0;
    int y = 0;

    bool operator==(const position& p_other) const {
        return x == p_other.x && y == p_other.y;
    }

    bool operator!=(const position& p_other) const {
        return !(*this == p_other);
    }

    position operator*(const int p_value) const {
        return { x * p_value, y * p_value };
    }

    position operator+(const int p_value) const {
        return { x + p_value, y + p_value };
    }

    position operator+(const position& p_value) const {
        return { x + p_value.x, y + p_value.y };
    }
};
