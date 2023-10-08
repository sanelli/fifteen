#pragma once

#include <cstddef>
#include <array>
#include <utility>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>
#include <vector>
#include <iostream>
#include <iomanip>

#include <tile_position.h>
#include <fifteen_error.h>

namespace fifteen
{
    template <std::size_t N>
    class fifteen_board
    {
        using itemType_t = unsigned short;
        static_assert(N >= 4 && N <= 16, "N must be between 4 and 16 (included)");

    private:
        std::array<itemType_t, N * N> tiles;
        tile_position emptyTile{N - 1, N - 1};

        constexpr unsigned int numberOfTiles() const
        {
            return N * N;
        }

        constexpr itemType_t getEmptyTileValue() const
        {
            return 0;
        }

        void validateRowAndColumn(tile_position &tile) const
        {
            if (tile.row >= N || tile.col >= N)
            {
                throw fifteen::fifteen_error("invalid row or column");
            }
        }

        tile_position::type getIndex(tile_position &tile) const noexcept
        {
            auto index = tile.row * N + tile.col;
            assert(index < numberOfTiles());
            return index;
        }

    public:
        fifteen_board()
        {
            reset();
        }

        itemType_t operator[](tile_position &&tile) const
        {
            validateRowAndColumn(tile);
            auto index = getIndex(tile);
            return tiles[index];
        }

        bool solved() const noexcept
        {
            for (auto index = 0; index < (static_cast<signed int>(numberOfTiles()) - 2); ++index)
            {
                if (tiles[index] != index + 1)
                {
                    return false;
                }
            }

            return tiles[numberOfTiles() - 1] == 0;
        }

        void reset() noexcept
        {
            for (auto index = 0u; index < numberOfTiles() - 1; ++index)
            {
                tiles[index] = index + 1;
            }
            tiles[numberOfTiles() - 1] = getEmptyTileValue();
            emptyTile.set(N - 1, N - 1);
        }

        void shuffle() noexcept
        {
            reset();
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(tiles.begin(), std::prev(tiles.end()), std::default_random_engine(seed));
        }

        void printout() const noexcept
        {
            std::cout << "-------------------------" << std::endl;
            std::cout << std::right;
            for (unsigned int row = 0; row < N; ++row)
            {
                std::cout << "|";
                for (unsigned int column = 0; column < N; ++column)
                {
                    auto value = operator[]({row, column});
                    if (value == getEmptyTileValue())
                    {
                        std::cout << std::setw(4) << "XXX" << std::setw(0) << " |";
                    }
                    else
                    {
                        std::cout << std::setw(4) << value << std::setw(0) << " |";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::left;
        }

        bool canMove(tile_position &&tile) const noexcept
        {
            return emptyTile.isAround(tile);
        }

        void move(tile_position &&tile)
        {
            if (emptyTile.isAround(tile))
            {
                auto emptyTileIndex = getIndex(emptyTile);
                auto tileIndex = getIndex(tile);

                tiles[emptyTileIndex] = tiles[tileIndex];
                tiles[tileIndex] = getEmptyTileValue();
                emptyTile = tile;
            }
            else
            {
                throw fifteen_error("tile cannot be moved");
            }
        }

        bool canMove(tile_move_action action) const noexcept
        {
            auto signedRow = static_cast<signed>(emptyTile.row);
            auto signedCol = static_cast<signed>(emptyTile.col);
            auto aboveRow = signedRow - 1;
            auto belowRow = signedRow + 1;
            auto leftCol = signedCol - 1;
            auto rightCol = signedCol + 1;

            switch (action)
            {
            case tile_move_action::up:
                return belowRow >= 0L && belowRow < static_cast<signed>(N);
                break;
            case tile_move_action::down:
                return aboveRow >= 0L && aboveRow < static_cast<signed>(N);
                break;
            case tile_move_action::left:
                return rightCol >= 0L && rightCol < static_cast<signed>(N);
                break;
            case tile_move_action::right:
                return leftCol >= 0L && leftCol < static_cast<signed>(N);
                break;
            }
        }

        void move(tile_move_action action)
        {
            if (canMove(action))
            {
                switch (action)
                {
                case tile_move_action::up:
                    move({emptyTile.row + 1, emptyTile.col});
                    break;
                case tile_move_action::down:
                    move({emptyTile.row - 1, emptyTile.col});
                    break;
                case tile_move_action::left:
                    move({emptyTile.row, emptyTile.col + 1});
                    break;
                case tile_move_action::right:
                    move({emptyTile.row, emptyTile.col - 1});
                    break;
                }
            }
            else
            {
                throw fifteen_error("cannot find a tile that can be moved in the specified direction");
            }
        }
    };
}