#include <cstdlib>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <fifteen_application.h>

#define TILE_SIZE 100

namespace fifteen
{
    using tiles_array_size = typename std::array<SDL_Texture *, FIFTEEN_BOARD_SIZE * FIFTEEN_BOARD_SIZE>::size_type;
}

fifteen::fifteen_application::fifteen_application() noexcept
{
    solved = false;
    processing = true;
    font_color = {0xFF, 0xFF, 0xFF, 0xFF};
    board.shuffle();

    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr, "error initializing SDL: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow("fifteen",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              FIFTEEN_BOARD_SIZE * TILE_SIZE,
                              FIFTEEN_BOARD_SIZE * TILE_SIZE + TILE_SIZE / 3,
                              SDL_WINDOW_SHOWN);

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

    font = TTF_OpenFont("./BebasNeue-Regular.ttf", 52);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    solved_font = TTF_OpenFont("./BebasNeue-Regular.ttf", 80);
    if (solved_font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Create the surfaces
    for (fifteen::tiles_array_size tileIndex = 0; tileIndex < tiles.size(); ++tileIndex)
    {
        const int tile_border = 1;

        auto tile_surface = SDL_CreateRGBSurface(0, TILE_SIZE, TILE_SIZE, 32, 0, 0, 0, 0);
        SDL_Rect tile_rect{.x = 0, .y = 0, .w = TILE_SIZE, .h = TILE_SIZE};
        SDL_Rect inner_tile_rect{.x = tile_border, .y = tile_border, .w = TILE_SIZE - tile_border, .h = TILE_SIZE - tile_border};
        auto red_color = SDL_MapRGBA(tile_surface->format, 0xFF, 0x00, 0x00, 0xFF);
        auto black_color = SDL_MapRGBA(tile_surface->format, 0x00, 0x00, 0x00, 0xFF);
        SDL_FillRect(tile_surface, &tile_rect, red_color);
        SDL_FillRect(tile_surface, &inner_tile_rect, black_color);

        // Add number only for values grater than zero
        if (tileIndex > 0)
        {
            auto number = std::to_string(tileIndex);
            SDL_Surface *text_surface = TTF_RenderText_Solid(font, number.c_str(), font_color);
            SDL_Rect text_target_rect{
                .x = (TILE_SIZE - text_surface->clip_rect.w) / 2,
                .y = (TILE_SIZE - text_surface->clip_rect.h) / 2,
                .w = text_surface->clip_rect.w,
                .h = text_surface->clip_rect.h};
            SDL_BlitSurface(text_surface, &text_surface->clip_rect, tile_surface, &text_target_rect);
            SDL_FreeSurface(text_surface);
        }

        tiles[tileIndex] = SDL_CreateTextureFromSurface(renderer, tile_surface);
        SDL_FreeSurface(tile_surface);
    }

    // Generate solved texture
    auto solved_surface = SDL_CreateRGBSurface(0, TILE_SIZE * FIFTEEN_BOARD_SIZE, TILE_SIZE * FIFTEEN_BOARD_SIZE, 32, 0, 0, 0, 0);
    auto solved_text_surface = TTF_RenderText_Solid(solved_font, "You win!", {0x00, 0xFF, 0x00, 0xFF});
    SDL_Rect solved_text_surface_rect{
        .x = (TILE_SIZE * FIFTEEN_BOARD_SIZE - solved_text_surface->clip_rect.w) / 2,
        .y = (TILE_SIZE * FIFTEEN_BOARD_SIZE - solved_text_surface->clip_rect.h) / 2,
        .w = solved_text_surface->clip_rect.w,
        .h = solved_text_surface->clip_rect.h
    };
    SDL_BlitSurface(solved_text_surface, &solved_text_surface->clip_rect, solved_surface, &solved_text_surface_rect);
    solved_texture = SDL_CreateTextureFromSurface(renderer, solved_surface);
    SDL_FreeSurface(solved_text_surface);
    SDL_FreeSurface(solved_surface);
}

fifteen::fifteen_application::~fifteen_application()
{
    TTF_CloseFont(font);
    TTF_CloseFont(solved_font);
    TTF_Quit();

    // Destroy the textures
    for (fifteen::tiles_array_size tileIndex = 0; tileIndex < tiles.size(); ++tileIndex)
    {
        SDL_DestroyTexture(tiles[tileIndex]);
    }

    SDL_DestroyTexture(solved_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int fifteen::fifteen_application::exit_code() const noexcept
{
    return EXIT_SUCCESS;
}

bool fifteen::fifteen_application::run() noexcept
{
    auto start = SDL_GetPerformanceCounter();

    process_events();
    render();
    cap_frame_rate(start);

    return processing;
}

void fifteen::fifteen_application::process_events() noexcept
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            processing = false;
            break;

        case SDL_MOUSEBUTTONUP:
        {
            if (!solved)
            {
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                auto col = mouse_x / TILE_SIZE;
                auto row = mouse_y / TILE_SIZE;
                if (col >= 0 &&
                    col < FIFTEEN_BOARD_SIZE &&
                    row >= 0 &&
                    row < FIFTEEN_BOARD_SIZE)
                {
                    tile_position tile{static_cast<tile_position::type>(row), static_cast<tile_position::type>(col)};
                    if (board.canMove(std::forward<tile_position>(tile)))
                    {
                        board.move(std::forward<tile_position>(tile));
                        solved = board.solved();
                    }
                }
            }
        }
        break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                if (!solved && board.canMove(fifteen::tile_move_action::up))
                {
                    board.move(fifteen::tile_move_action::up);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_DOWN:
                if (!solved && board.canMove(fifteen::tile_move_action::down))
                {
                    board.move(fifteen::tile_move_action::down);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_RIGHT:
                if (!solved && board.canMove(fifteen::tile_move_action::right))
                {
                    board.move(fifteen::tile_move_action::right);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_LEFT:
                if (!solved && board.canMove(fifteen::tile_move_action::left))
                {
                    board.move(fifteen::tile_move_action::left);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_N: // NEW GAME
                board.shuffle();
                solved = false;
                break;

            case SDL_SCANCODE_C: // CHEAT
                board.reset();
                solved = false;
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}

void fifteen::fifteen_application::render() const noexcept
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    if (solved)
    {
        SDL_Rect solved_texture_rect{
            .x = 0,
            .y = 0,
            .w = TILE_SIZE * FIFTEEN_BOARD_SIZE,
            .h = TILE_SIZE * FIFTEEN_BOARD_SIZE};
        SDL_RenderCopy(renderer, solved_texture, NULL, &solved_texture_rect);
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &solved_texture_rect);
    }
    else
    {
        for (tile_position::type row = 0; row < FIFTEEN_BOARD_SIZE; ++row)
        {
            for (tile_position::type col = 0; col < FIFTEEN_BOARD_SIZE; ++col)
            {
                SDL_Rect texture_rect{
                    .x = static_cast<int>(col * TILE_SIZE),
                    .y = static_cast<int>(row * TILE_SIZE),
                    .h = TILE_SIZE,
                    .w = TILE_SIZE};
                auto tile_number = board[{row, col}];
                SDL_Rect board_rectangle{
                    .x = 0,
                    .y = 0,
                    .w = TILE_SIZE * FIFTEEN_BOARD_SIZE,
                    .h = TILE_SIZE * FIFTEEN_BOARD_SIZE};
                SDL_RenderCopy(renderer, tiles[tile_number], NULL, &texture_rect);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderDrawRect(renderer, &board_rectangle);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void fifteen::fifteen_application::cap_frame_rate(Uint64 &start) const noexcept
{
    auto end = SDL_GetPerformanceCounter();
    auto elapsedMS = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f;
    SDL_Delay(std::max(0.00f, std::floor(16.666f - elapsedMS)));
}