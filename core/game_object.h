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

    SDL_Rect m_location;

public:
    game_object(const char p_id, const SDL_Rect& p_location, const texture_manager& p_manager);

    virtual ~game_object() = default;

public:
    char get_id() const;

    virtual void update() = 0;

    virtual void render();
};
