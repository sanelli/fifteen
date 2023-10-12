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

        tile_position(const tile_position::type r, const tile_position::type c) noexcept;
        tile_position& operator=(const tile_position& other) = default;
        bool isAboveOf(const tile_position &other) const noexcept;
        bool isBelowOf(const tile_position &other) const noexcept;
        bool isLeftOf(const tile_position &other) const noexcept;
        bool isRightOf(const tile_position &other) const noexcept;
        bool isAround(const tile_position &other) const noexcept;
    };
}