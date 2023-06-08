#include "window_pause.h"


#include <string>


window_pause::window_pause() :
    window_message("PAUSE", true)
{ }


void window_pause::show() {
    SDL_RenderPresent(m_renderer);
}
