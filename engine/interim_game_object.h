#pragma once


#include <chrono>

#include "core/game_object.h"


class interim_game_object : public game_object {
private:
    std::chrono::duration<std::chrono::milliseconds> m_live_time;

public:
    void update() override { }
};