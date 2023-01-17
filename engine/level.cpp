#include "level.h"

#include <fstream>


level::level(const std::string& p_path) :
    m_path(p_path)
{ }


bool level::is_valid() const {
    return !m_path.empty();
}


level_matrix level::load() const {
    std::ifstream stream(m_path);

    level_matrix matrix;

    for (std::string line; std::getline(stream, line); ) {
        matrix.push_back(line);
    }

    return matrix;
}