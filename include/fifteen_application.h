#pragma once

#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <fifteen_board.h>

#define FIFTEEN_BOARD_SIZE 4

namespace fifteen
{

    struct fifteen_application
    {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        fifteen::fifteen_board<FIFTEEN_BOARD_SIZE> board;
        std::array<SDL_Texture *, FIFTEEN_BOARD_SIZE * FIFTEEN_BOARD_SIZE> tiles;
        bool processing;
        bool solved;
        SDL_Texture *solved_texture;
        SDL_Texture *footer_texture;
        SDL_Rect footer_rect;
        SDL_Rect solved_texture_rect;
        TTF_Font *footer_font;
        int move_count;
        int rendered_move_count;
        SDL_Texture *counter_texture;
        SDL_Rect counter_rect;

        void process_events() noexcept;
        void render() noexcept;
        void cap_frame_rate(Uint64 &start) const noexcept;

    public:
        fifteen_application() noexcept;
        fifteen_application(const fifteen_application &) = delete;
        fifteen_application(fifteen_application &&) = delete;

        ~fifteen_application();

        fifteen_application &operator=(const fifteen_application &) = delete;
        fifteen_application &operator=(fifteen_application &&) = delete;

        bool run() noexcept;
        int exit_code() const noexcept;
    };

}