#include <tile_position.h>

fifteen::tile_position::tile_position(fifteen::tile_position::type r, fifteen::tile_position::type c) noexcept : row(r), col(c) {}

void fifteen::tile_position::set(fifteen::tile_position::type r, fifteen::tile_position::type c)
{
    row = r;
    col = c;
}

bool fifteen::tile_position::isAboveOf(fifteen::tile_position &other) const noexcept
{
    return row == other.row + 1 && col == other.col;
}

bool fifteen::tile_position::isBelowOf(fifteen::tile_position &other) const noexcept
{
    return row == other.row - 1 && col == other.col;
}

bool fifteen::tile_position::isLeftOf(fifteen::tile_position &other) const noexcept
{
    return row == other.row && col == other.col + 1;
}

bool fifteen::tile_position::isRightOf(fifteen::tile_position &other) const noexcept
{
    return row == other.row && col == other.col - 1;
}

bool fifteen::tile_position::isAround(fifteen::tile_position &other) const noexcept
{
    return isAboveOf(other) || isBelowOf(other) || isLeftOf(other) || isRightOf(other);
}