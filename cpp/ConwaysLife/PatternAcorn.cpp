#include "PatternAcorn.hpp"

bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    switch(y)
    {
        case 0:
            if (x == 1)
            {
                return true;
            }
            return false;
        case 1:
            if (x == 3)
            {
                return true;
            }
            return false;
        case 2:
            switch(x)
            {
                case 0: [[fallthrough]];
                case 1: [[fallthrough]];
                case 4: [[fallthrough]];
                case 5: [[fallthrough]];
                case 6: 
                    return true;
                return false;
            }
            return false;
        default:
            return false;
    }

    // if (y == 0)
    // {
    //     if (x == 1)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }
    // else if (y == 1)
    // {
    //     if (x == 3)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }
    // else if (y == 2)
    // {
    //     if ((x >= 2 && x <= 3) || (x < 0 && x > 7))
    //     {
    //         return false;
    //     }
    //     else
    //     {
    //         return true;
    //     }
    // }
    // else
    // {
    //     return false;
    // }
}
