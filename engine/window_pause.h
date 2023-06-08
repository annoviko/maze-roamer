#pragma once


#include "window_message.h"


class window_pause : public window_message {
public:
    window_pause();

public:
    void show() override;
};
