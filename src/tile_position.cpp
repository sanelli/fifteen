#include <tile_position.h>

fifteen::tile_position::tile_position(const fifteen::tile_position::type r, const fifteen::tile_position::type c) noexcept : row(r), col(c) {}

bool fifteen::tile_position::isAboveOf(const fifteen::tile_position &other) const noexcept
{
    return row == other.row + 1 && col == other.col;
}

bool fifteen::tile_position::isBelowOf(const fifteen::tile_position &other) const noexcept
{
    return row == other.row - 1 && col == other.col;
}

bool fifteen::tile_position::isLeftOf(const fifteen::tile_position &other) const noexcept
{
    return row == other.row && col == other.col + 1;
}

bool fifteen::tile_position::isRightOf(const fifteen::tile_position &other) const noexcept
{
    return row == other.row && col == other.col - 1;
}

bool fifteen::tile_position::isAround(const fifteen::tile_position &other) const noexcept
{
    return isAboveOf(other) || isBelowOf(other) || isLeftOf(other) || isRightOf(other);
}