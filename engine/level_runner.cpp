#include "level_runner.h"


#include "maze.h"


level_runner::level_runner(const player_context::ptr& p_context) :
    m_context(p_context),
    m_is_running(true)
{ }


void level_runner::run(const level& p_level) {
    maze m(p_level, m_context);
    m.render();

    SDL_Event event;
    std::memset((void*)&event, 0x00, sizeof(SDL_Event));

    while (m_is_running && m.is_running()) {
        auto frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                m_is_running = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    m.get_player()->move_right();
                    break;

                case SDLK_LEFT:
                    m.get_player()->move_left();
                    break;

                case SDLK_UP:
                    m.get_player()->move_up();
                    break;

                case SDLK_DOWN:
                    m.get_player()->move_down();
                    break;

                case SDLK_b:
                    m.activate_bomb();
                    break;
                }

                break;

            default:
                break;
            }
        }

        m.update();
        m.render();

        auto frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < 20)
        {
            SDL_Delay((int)(20 - frameTime));
        }
    }
}


bool level_runner::is_game_over() const {
    return !m_is_running || m_context->is_dead();
}
