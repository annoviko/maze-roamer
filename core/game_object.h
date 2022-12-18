#pragma once

#include <memory>

#include "position.h"
#include "texture_manager.h"


class game_object {
public:
    using ptr = std::shared_ptr<game_object>;

protected:
    const char m_id;
    const texture_manager& m_texture_manager;

    int m_current_row;
    int m_current_frame;
    int m_num_of_frame;
    SDL_RendererFlip m_flip;

    SDL_Rect m_location;

public:
    game_object(const char p_id, const SDL_Rect& p_location, const texture_manager& p_manager, const int p_current_row, const int p_current_frame, const int p_num_of_frame, const SDL_RendererFlip p_flip);

    virtual ~game_object() = default;

public:
    char get_id() const;

    virtual void update() = 0;

    virtual void render();
};
