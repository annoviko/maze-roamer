#pragma once


#include <string>

#include "level_matrix.h"


class level {
private:
    std::string m_path;

public:
    level() = default;

    level(const std::string& p_path);

public:
    bool is_valid() const;

    level_matrix load() const;
};