#pragma once


#include <filesystem>
#include <string>

#include "scenario.h"


class level_finder {
private:
    std::vector<scenario> m_levels;

public:
    level_finder(const std::string& p_directory);

public:
    const std::vector<scenario>& get_levels() const;

private:
    bool is_level_file(const std::filesystem::directory_entry& p_entry) const;
};
