#include "game_status_widget.h"

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "core/painter.h"

#include "engine/bomb.h"
#include "engine/booster_speed.h"


game_status_widget::game_status_widget(SDL_Renderer* p_renderer, const texture_manager& p_texture_manager, const int p_x, const int p_y, const player_context::ptr& p_context, const level_stats::ptr& p_level_stats) :
    m_renderer(p_renderer),
    m_texture_manager(p_texture_manager),
    m_x(p_x), m_y(p_y),
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
    SDL_Rect rect = { m_x, m_y, get_width(), get_height() };

    SDL_SetRenderDrawColor(m_renderer, 0xff, 0x5b, 0x00, 0xff);
    SDL_RenderFillRect(m_renderer, &rect);

    show_score();
    show_health();
    show_progress();
    show_boost_speed();
    show_inventory();

    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
}


void game_status_widget::show_health() {
    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, "Health:", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { m_x + 650, m_y - FONT_Y_DRIFT, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    const int health = m_player_context->get_health();

    SDL_Rect location = { m_x + HEALTH_X_OFFSET, m_y, 32, 32 };
    m_texture_manager.draw_frame_wo_offset(location, 10, health < 3, SDL_FLIP_NONE);

    location = { m_x + HEALTH_X_OFFSET + WIDGET_CELL_SIZE, m_y, 32, 32 };
    m_texture_manager.draw_frame_wo_offset(location, 10, health < 2, SDL_FLIP_NONE);

    location = { m_x + HEALTH_X_OFFSET + 2 * WIDGET_CELL_SIZE, m_y, 32, 32 };
    m_texture_manager.draw_frame_wo_offset(location, 10, health < 1, SDL_FLIP_NONE);
}


void game_status_widget::show_score() {
    std::string message("Score: ");
    const int score = m_player_context->get_score();
    if (score == 0) {
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
    SDL_Rect dstrect = { m_x + 5, m_y - FONT_Y_DRIFT, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}


void game_status_widget::show_progress() {
    SDL_Rect progress = { m_x + PROGRESS_BAR_X_OFFSET, m_y + PROGRESS_BAR_HEIGHT / 2 + PROGRESS_BAR_BORDER_SIZE, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT };
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
    std::string message("Boost Speed: ");

    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, message.c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { m_x + 5, m_y + WIDGET_CELL_SIZE - FONT_Y_DRIFT, texW, texH };

    SDL_RenderCopy(m_renderer, Message, NULL, &dstrect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    /* show progress bar (TODO: refactor to move it to common functionality) */
    SDL_Rect progress = { m_x + PROGRESS_BAR_X_OFFSET, m_y + WIDGET_CELL_SIZE + PROGRESS_BAR_HEIGHT / 2, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT };
    SDL_Rect border = { progress.x - 3, progress.y - 3, progress.w + 6, progress.h + 6 };
    SDL_SetRenderDrawColor(m_renderer, 0x5a, 0x74, 0x7a, 0xff);
    SDL_RenderFillRect(m_renderer, &border);
    SDL_SetRenderDrawColor(m_renderer, 0x18, 0x37, 0x3d, 0xff);
    SDL_RenderFillRect(m_renderer, &progress);

    double percentage = 0.0;
    if (m_player_context->is_booster_active(inventory_object_t::BOOSTER_SPEED)) {
        auto& booster = m_player_context->get_booster();
        percentage = progress.w * booster.get_remaining_time_ms() / booster.get_total_duration_time_ms();
    }

    SDL_Rect progress_value = { progress.x, progress.y, (int)percentage, progress.h };
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xb6, 0x30, 0xff);
    SDL_RenderFillRect(m_renderer, &progress_value);
}


void game_status_widget::show_inventory() {
    auto inventory_objects = m_player_context->get_inventory().get_objects_as_stack();
    auto iter_object = inventory_objects.begin();

    int slot = 0;

    auto painter_handler = painter(m_renderer);

    for (int i = 0; i < INVENTORY_SLOTS; i++, slot++) {
        int sprite_row = -1;
        int sprite_col = -1;
        int count = 0;

        if (iter_object != inventory_objects.end()) {
            count = m_player_context->get_inventory().get_amount(*iter_object);

            switch (*iter_object) {
            case inventory_object_t::BOMB:
                sprite_row = bomb::SPRITE_ROW;
                sprite_col = bomb::SPRITE_COL;
                break;

            case inventory_object_t::BOOSTER_SPEED:
                sprite_row = booster_speed::SPRITE_ROW;
                sprite_col = booster_speed::SPRITE_COL;
                break;
            }

            iter_object++;
        }

        SDL_Rect location = { m_x + INVENTORY_X_OFFSET + WIDGET_CELL_SIZE * slot, m_y + INVENTORY_Y_OFFSET, WIDGET_CELL_SIZE, 32 };
        SDL_Rect location_count = { m_x + INVENTORY_X_OFFSET + WIDGET_CELL_SIZE * slot, m_y + INVENTORY_Y_OFFSET + WIDGET_CELL_SIZE, WIDGET_CELL_SIZE + 1, 16 };

        rgba frame_color = { 220, 220, 220, 255 };

        if ((sprite_row < 0) || (sprite_col < 0)) {
            painter_handler.draw_rectangle(location, { 0, 0, 0, 255 });
            painter_handler.draw_frame(location, frame_color);
        }
        else {
            painter_handler.draw_rectangle(location, { 0, 0, 0, 255 });
            m_texture_manager.draw_frame_wo_offset(location, sprite_row, sprite_col, SDL_FLIP_NONE);
            painter_handler.draw_frame(location, frame_color);
        }

        painter_handler.draw_rectangle(location_count, frame_color);

        SDL_Color white_color = { 255, 255, 255 };
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, std::to_string(count).c_str(), white_color);
        SDL_Texture* count_texture = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

        int text_width = 0;
        int text_height = 0;
        SDL_QueryTexture(count_texture, NULL, NULL, &text_width, &text_height);
        SDL_Rect dst_rect = { m_x + INVENTORY_X_OFFSET + WIDGET_CELL_SIZE * slot + 16, m_y + INVENTORY_Y_OFFSET + 16, text_width, text_height };

        SDL_RenderCopy(m_renderer, count_texture, NULL, &dst_rect);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(count_texture);
    }
}