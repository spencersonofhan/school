#include "PatternGlider.hpp"

bool PatternGlider::getCell(std::uint8_t x, std::uint8_t y) const
{
    switch (y)
    {
        case 0:
            if (x == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        case 1:
            if (x == 1 || x == 2)
            {
                return true;
            }
            else
            {
                return false;
            }
        case 2:
            if (x == 0 || x == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        default:
            return false;
    }
}
