#pragma once


#include <filesystem>
#include <string>

#include "level.h"


class level_finder {
private:
    std::vector<level> m_levels;

public:
    level_finder(const std::string& p_directory);

public:
    const std::vector<level>& get_levels() const;

private:
    bool is_level_file(const std::filesystem::directory_entry& p_entry) const;
};
