#include "game_status_widget.h"

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>


game_status_widget::game_status_widget(SDL_Renderer* p_renderer, const texture_manager& p_texture_manager, const int p_x, const int p_y, const player_context::ptr& p_context, const level_stats::ptr& p_level_stats) :
    m_renderer(p_renderer),
    m_texture_manager(p_texture_manager),
    m_x(p_x), m_y(p_y), 
    m_w(p_x + get_width()), m_h(p_y + get_height()),
    m_player_context(p_context),
    m_level_stats(p_level_stats)
{ }


int game_status_widget::get_height() {
    return WIDGET_ROWS * WIDGET_CELL_SIZE;
}


int game_status_widget::get_width() {
    return WIDGET_COLS * WIDGET_CELL_SIZE;
}


void game_status_widget::render() {
    SDL_Rect rect = { 0, m_y, m_w, m_h };

    SDL_SetRenderDrawColor(m_renderer, 0xff, 0x5b, 0x00, 0xff);
    SDL_RenderFillRect(m_renderer, &rect);

    show_score();
    show_health();
    show_progress();
    show_boost_speed();
}


void game_status_widget::show_health() {
    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, "Health:", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 595, m_y - FONT_Y_DRIFT, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    const int health = m_player_context->get_health();

    SDL_Rect location = { 736, m_y, 32, 32 };
    m_texture_manager.draw_frame(location, 10, health < 3, SDL_FLIP_NONE);
    location = { 768, m_y, 32, 32 };
    m_texture_manager.draw_frame(location, 10, health < 2, SDL_FLIP_NONE);
    location = { 800, m_y, 32, 32 };
    m_texture_manager.draw_frame(location, 10, health < 1, SDL_FLIP_NONE);
}


void game_status_widget::show_score() {
    std::string message("Score: ");
    const int score = m_player_context->get_score();
    if (score == 0)
    {
        message.append("00000");
    }
    else {
        int cnt = 5 - (int)log10(score);
        while (cnt > 0)
        {
            cnt--;
            message.append("0");
        }
        message.append(std::to_string(score));
    }
    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, message.c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 5, m_y - FONT_Y_DRIFT, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}


void game_status_widget::show_progress() {
    SDL_Rect progress = { 278, m_y + PROGRESS_BAR_HEIGHT / 2 + PROGRESS_BAR_BORDER_SIZE, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT };
    SDL_Rect border = { progress.x - PROGRESS_BAR_BORDER_SIZE, progress.y - PROGRESS_BAR_BORDER_SIZE, progress.w + 6, progress.h + 6 };
    SDL_SetRenderDrawColor(m_renderer, 0x5a, 0x74, 0x7a, 0xff);
    SDL_RenderFillRect(m_renderer, &border);
    SDL_SetRenderDrawColor(m_renderer, 0x18, 0x37, 0x3d, 0xff);
    SDL_RenderFillRect(m_renderer, &progress);
    double percentage = progress.w * m_level_stats->get_collected_coins() / (double)m_level_stats->get_total_coins();
    SDL_Rect progress_value = { progress.x, progress.y, (int)percentage, progress.h };
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xb6, 0x30, 0xff);
    SDL_RenderFillRect(m_renderer, &progress_value);
}


void game_status_widget::show_boost_speed() {
    /* show message (TODO: refactor to move it to common functionality) */
    std::string message("BOOST SPEED: ");

    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, message.c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 5, m_y + WIDGET_CELL_SIZE - FONT_Y_DRIFT, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    /* show progress bar (TODO: refactor to move it to common functionality) */
    SDL_Rect progress = { 278, m_y + WIDGET_CELL_SIZE + PROGRESS_BAR_HEIGHT / 2, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT };
    SDL_Rect border = { progress.x - 3, progress.y - 3, progress.w + 6, progress.h + 6 };
    SDL_SetRenderDrawColor(m_renderer, 0x5a, 0x74, 0x7a, 0xff);
    SDL_RenderFillRect(m_renderer, &border);
    SDL_SetRenderDrawColor(m_renderer, 0x18, 0x37, 0x3d, 0xff);
    SDL_RenderFillRect(m_renderer, &progress);

    double percentage = 0.0;
    if (m_player_context->get_speed_booster().is_active()) {
        percentage = progress.w * m_player_context->get_speed_booster().get_remaining_time_ms() / m_player_context->get_speed_booster().get_total_duration_time_ms();
    }

    SDL_Rect progress_value = { progress.x, progress.y, (int)percentage, progress.h };
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xb6, 0x30, 0xff);
    SDL_RenderFillRect(m_renderer, &progress_value);
}
