#include "font_manager.h"


const std::unordered_map<font_value_t, std::string> font_manager::FONT_NAME_DICT = {
    { font_value_t::CONFESSION_FULL_REGULAR, "fonts/the-confession-full-regular.ttf" },
};


TTF_Font* font_manager::get_font(const font_value_t p_type, const int p_size) {
    auto iter_name = FONT_NAME_DICT.find(p_type);
    if (iter_name == FONT_NAME_DICT.end()) {
        throw std::exception("unknown font type");
    }

    auto iter_type = m_font_cache.find(p_type);
    if (iter_type == m_font_cache.end()) {
        m_font_cache[p_type][p_size] = TTF_OpenFont(iter_name->second.c_str(), p_size);
    }

    auto iter_size = m_font_cache[p_type].find(p_size);
    if (iter_size == m_font_cache[p_type].end()) {
        m_font_cache[p_type][p_size] = TTF_OpenFont(iter_name->second.c_str(), p_size);
    }

    return m_font_cache[p_type][p_size];
}
