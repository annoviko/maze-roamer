#include "level_runner.h"


#include "maze.h"


level_runner::level_runner(SDL_Renderer* p_renderer, const player_context::ptr& p_context) :
    m_renderer(p_renderer),
    m_context(p_context),
    m_is_running(true)
{ }


void level_runner::run(const level& p_level) {
    maze m(p_level, m_context, m_renderer);
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
                    m.move_right();
                    break;

                case SDLK_LEFT:
                    m.move_left();
                    break;

                case SDLK_UP:
                    m.move_up();
                    break;

                case SDLK_DOWN:
                    m.move_down();
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