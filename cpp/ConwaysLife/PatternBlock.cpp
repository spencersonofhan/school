#include "PatternBlock.hpp"

bool PatternBlock::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= 2 || y >= 2)
    {
        return false;
    }
    return true;
}
