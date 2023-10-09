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
    counter_texture = nullptr;
    move_count = 0;
    rendered_move_count = move_count - 1;
    solved = false;
    processing = true;
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

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Create the texture of the tiles
    TTF_Font *tiles_font = TTF_OpenFont("./BebasNeue-Regular.ttf", 52);
    if (tiles_font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

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
            SDL_Surface *text_surface = TTF_RenderText_Solid(tiles_font, number.c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
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
    TTF_CloseFont(tiles_font);

    // Generate solved texture
    TTF_Font *solved_font = TTF_OpenFont("./BebasNeue-Regular.ttf", 80);
    if (solved_font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    auto solved_surface = TTF_RenderText_Solid(solved_font, "You win!", {0x00, 0xFF, 0x00, 0xFF});
    solved_texture_rect.x = (TILE_SIZE * FIFTEEN_BOARD_SIZE - solved_surface->clip_rect.w) / 2;
    solved_texture_rect.y = (TILE_SIZE * FIFTEEN_BOARD_SIZE - solved_surface->clip_rect.h) / 2;
    solved_texture_rect.w = solved_surface->clip_rect.w;
    solved_texture_rect.h = solved_surface->clip_rect.h;
    solved_texture = SDL_CreateTextureFromSurface(renderer, solved_surface);
    SDL_FreeSurface(solved_surface);
    TTF_CloseFont(solved_font);

    // Footer texture
    footer_font = TTF_OpenFont("./BebasNeue-Regular.ttf", 20);
    if (footer_font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    auto footer_surface = TTF_RenderText_Solid(footer_font, "N: New game | Arrow/Mouse: Move", {0xFF, 0xFF, 0xFF, 0xFF});
    footer_rect.x = 1;
    footer_rect.y = TILE_SIZE * FIFTEEN_BOARD_SIZE + (TILE_SIZE / 3 - footer_surface->clip_rect.h) / 2;
    footer_rect.w = footer_surface->clip_rect.w;
    footer_rect.h = footer_surface->clip_rect.h;
    footer_texture = SDL_CreateTextureFromSurface(renderer, footer_surface);
    SDL_FreeSurface(footer_surface);
}

fifteen::fifteen_application::~fifteen_application()
{
    TTF_CloseFont(footer_font);
    TTF_Quit();

    // Destroy the textures
    for (fifteen::tiles_array_size tileIndex = 0; tileIndex < tiles.size(); ++tileIndex)
    {
        SDL_DestroyTexture(tiles[tileIndex]);
    }

    if (counter_texture != nullptr)
    {
        SDL_DestroyTexture(counter_texture);
    }
    SDL_DestroyTexture(footer_texture);
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
                        ++move_count;
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
                    ++move_count;
                    board.move(fifteen::tile_move_action::up);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_DOWN:
                if (!solved && board.canMove(fifteen::tile_move_action::down))
                {
                    ++move_count;
                    board.move(fifteen::tile_move_action::down);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_RIGHT:
                if (!solved && board.canMove(fifteen::tile_move_action::right))
                {
                    ++move_count;
                    board.move(fifteen::tile_move_action::right);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_LEFT:
                if (!solved && board.canMove(fifteen::tile_move_action::left))
                {
                    ++move_count;
                    board.move(fifteen::tile_move_action::left);
                    solved = board.solved();
                }
                break;

            case SDL_SCANCODE_N: // NEW GAME
                move_count = 0;
                board.shuffle();
                solved = false;
                break;

            case SDL_SCANCODE_C: // CHEAT
                if (!solved)
                {
                    board.reset();
                }
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

void fifteen::fifteen_application::render() noexcept
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    // Render footer
    if (rendered_move_count != move_count)
    {
        auto counter_text = std::string("Moves: ") + std::to_string(move_count);
        auto counter_text_surface = TTF_RenderText_Solid(footer_font, counter_text.c_str(), {0xFF, 0xFF, 0xFF, 0xFF});

        if (counter_texture != nullptr)
        {
            SDL_DestroyTexture(counter_texture);
        }
        counter_texture = SDL_CreateTextureFromSurface(renderer, counter_text_surface);
        counter_rect.x = TILE_SIZE * FIFTEEN_BOARD_SIZE - counter_text_surface->clip_rect.w - 5;
        counter_rect.y = TILE_SIZE * FIFTEEN_BOARD_SIZE + (TILE_SIZE / 3 - counter_text_surface->clip_rect.h) / 2;
        counter_rect.w = counter_text_surface->clip_rect.w;
        counter_rect.h = counter_text_surface->clip_rect.h;
        SDL_FreeSurface(counter_text_surface);
        rendered_move_count = move_count;
    }

    SDL_RenderCopy(renderer, footer_texture, NULL, &footer_rect);
    SDL_RenderCopy(renderer, counter_texture, NULL, &counter_rect);

    // Render board
    if (solved)
    {
        SDL_RenderCopy(renderer, solved_texture, NULL, &solved_texture_rect);
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
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