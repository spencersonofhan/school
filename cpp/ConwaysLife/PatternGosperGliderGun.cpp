#include "PatternGosperGliderGun.hpp"

bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    switch(y)
    {
        case 0:
            if(x == 24){return true;}
            else{return false;}
        case 1:
            if(x == 22 || x == 24){return true;}
            else{return false;}
        case 2:
            if((x >= 12 && x <= 13) || (x >= 20 && x <= 21)){return true;}
            else{return false;}
        case 3:
            if(x == 11 || x == 15 || (x >= 20 && x <= 21)){return true;}
            else{return false;}
        case 4:
            if(x <= 1 || x == 10 ||
            x == 16 || (x >= 20 && x <= 21)){return true;}
            else{return false;}
        case 5:
            if(x <= 1 || x == 10 || x ==14
            || (x >= 16 && x <= 17) || x == 22 || x == 24){return true;}
            else{return false;}
        case 6:
            if(x == 10 || x == 16 || x == 24){return true;}
            else{return false;}
        case 7:
            if(x == 11 || x == 15){return true;}
            else{return false;}
        case 8:
            if(x == 12 || x == 13){return true;}
            else{return false;}
        default:
            return false;
    }
}
