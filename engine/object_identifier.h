#pragma once


class object_identifier {
public:
    static bool is_hurdle(const char p_id) {
        return (p_id == '*') || (p_id == '^');
    }
};
