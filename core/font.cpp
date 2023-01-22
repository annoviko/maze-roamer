#include "font.h"


#include <filesystem>


font::font(const std::string& p_font_path, const int p_font_size) {
    if (!std::filesystem::exists(p_font_path)) {
        throw std::invalid_argument("font '" + p_font_path + "' is not found");
    }

    m_font = TTF_OpenFont(p_font_path.c_str(), p_font_size);
    m_size = p_font_size;
}


font::~font() {
    if (m_font != nullptr) {
        TTF_CloseFont(m_font);
    }
}


int font::get_size() const {
    return m_size;
}


TTF_Font* font::operator()() {
    return m_font;
}