#pragma once


#include <unordered_map>

#include "font.h"
#include "singleton.h"


enum class font_value_t {
    CONFESSION_FULL_REGULAR
};


class font_manager : public singleton<font_manager> {
private:
    const static std::unordered_map<font_value_t, std::string> FONT_NAME_DICT;

private:
    std::unordered_map <font_value_t, std::unordered_map<int, TTF_Font*>> m_font_cache;

public:
    TTF_Font* get_font(const font_value_t p_type, const int p_size);
};