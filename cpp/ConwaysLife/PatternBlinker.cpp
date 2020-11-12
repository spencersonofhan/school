#include "PatternBlinker.hpp"

bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= 3 || y >= 1)
    {
        return false;
    }
    return true;
}
