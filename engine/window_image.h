#pragma once


#include <string>

#include "window_base.h"


class window_image : public window_base {
private:
    std::string m_path;

public:
    window_image(const std::string& p_path);
};
