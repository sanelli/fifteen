#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "fifteen.h"

#define FIFTEEN_BOARD_SIZE 4;

int main()
{
    fifteen::fifteen_board<4> board;
    board.shuffle();

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *window = SDL_CreateWindow("fifteen",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          300, 300, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "cannot initalize font\n");
        exit(EXIT_FAILURE);
    }

    TTF_Font *font = TTF_OpenFont("./BebasNeue-Regular.ttf", 12);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    auto processing = true;
    while (processing)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                processing = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    if (board.canMove(fifteen::tile_move_action::up))
                    {
                        board.move(fifteen::tile_move_action::up);
                    }
                    break;

                case SDL_SCANCODE_DOWN:
                    if (board.canMove(fifteen::tile_move_action::down))
                    {
                        board.move(fifteen::tile_move_action::down);
                    }
                    break;

                case SDL_SCANCODE_RIGHT:
                    if (board.canMove(fifteen::tile_move_action::right))
                    {
                        board.move(fifteen::tile_move_action::right);
                    }
                    break;

                case SDL_SCANCODE_LEFT:
                    if (board.canMove(fifteen::tile_move_action::left))
                    {
                        board.move(fifteen::tile_move_action::left);
                    }
                    break;

                default:
                    break;
                }
                board.printout();
                break;

            default:
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    return EXIT_SUCCESS;
}