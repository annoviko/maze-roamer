#include "level_finder.h"

#include <regex>


level_finder::level_finder(const std::string& p_directory) {
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(p_directory)) {
        if (is_level_file(entry)) {
            m_levels.emplace_back(entry.path().string());
        }
    }
}


const std::vector<level>& level_finder::get_levels() const {
    return m_levels;
}


bool level_finder::is_level_file(const std::filesystem::directory_entry& p_entry) const {
    if (!p_entry.is_regular_file()) {
        return false;
    }

    const std::string filename = p_entry.path().filename().string();

    std::regex pattern("level-(\\d+).txt");
    std::smatch result;

    if (!std::regex_search(filename, result, pattern)) {
        return false;
    }

    return true;
}
