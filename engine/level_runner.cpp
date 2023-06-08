#include "level_runner.h"


#include "core/game_time.h"

#include "engine/window_pause.h"

#include "maze.h"


level_runner::level_runner(const player_context::ptr& p_context) :
    m_context(p_context),
    m_is_running(true),
    m_is_pause(false)
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
                case SDLK_d:
                    m.get_player()->move_right();
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    m.get_player()->move_left();
                    break;

                case SDLK_UP:
                case SDLK_w:
                    m.get_player()->move_up();
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    m.get_player()->move_down();
                    break;

                case SDLK_b:
                    m.activate_bomb();
                    break;

                case SDLK_p:
                case SDLK_PAUSE:
                    m_is_pause = !m_is_pause;

                    if (m_is_pause) {
                        window_pause().show();
                        game_time::get().pause();
                    }
                    else {
                        game_time::get().resume();
                    }

                    break;

                case SDLK_ESCAPE:
                    m_is_running = false;
                    break;
                }

                break;

            default:
                break;
            }
        }

        if (!m_is_pause) {
            m.update();
            m.render();
        }

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
