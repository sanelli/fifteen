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
        TTF_Font *font;
        TTF_Font *solved_font;
        SDL_Renderer *renderer;
        fifteen::fifteen_board<FIFTEEN_BOARD_SIZE> board;
        std::array<SDL_Texture *, FIFTEEN_BOARD_SIZE * FIFTEEN_BOARD_SIZE> tiles;
        bool processing;
        bool solved;
        SDL_Color font_color;
        SDL_Texture *solved_texture;
        
        void process_events() noexcept;
        void render() const noexcept;
        void cap_frame_rate(Uint64 &start) const noexcept;

    public:
        fifteen_application() noexcept;
        ~fifteen_application();

        bool run() noexcept;
        int exit_code() const noexcept;
    };

}