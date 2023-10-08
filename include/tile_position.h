#pragma once

namespace fifteen
{
    enum class tile_move_action
    {
        up,
        down,
        left,
        right
    };

    struct tile_position
    {
        using type = unsigned int;
        tile_position::type row;
        tile_position::type col;

        tile_position(tile_position::type r, tile_position::type c) noexcept;
        tile_position& operator=(const tile_position& other) = default;
        void set(tile_position::type r, tile_position::type c);
        bool isAboveOf(tile_position &other) const noexcept;
        bool isBelowOf(tile_position &other) const noexcept;
        bool isLeftOf(tile_position &other) const noexcept;
        bool isRightOf(tile_position &other) const noexcept;
        bool isAround(tile_position &other) const noexcept;
    };
}