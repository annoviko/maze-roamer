#pragma once


#include <string>

#include <SDL.h>

#include "core/graphic_context.h"
#include "core/rgba.h"

#include "window_base.h"


class window_message : public window_base {
public:
    window_message(const std::string& p_message, const bool p_resize_to_message = false);
};