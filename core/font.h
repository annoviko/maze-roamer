#pragma once


#include <string>

#include <SDL_ttf.h>


class font {
private:
    TTF_Font* m_font;
    int m_size = -1;

public:
    font(const std::string& p_font_path, const int p_font_size);

    ~font();

public:
    int get_size() const;

public:
    TTF_Font* operator()();
};