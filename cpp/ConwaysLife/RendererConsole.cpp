#include "RendererConsole.hpp"

void RendererConsole::render(const LifeSimulator& simulation)
{
    rlutil::cls();
    rlutil::hidecursor();
    for(uint8_t y = 0; y < simulation.getSizeY(); y++)
    {
        for(uint8_t x = 0; x < simulation.getSizeX(); x++)
        {
            if (simulation.getCell(x, y))
            {
                rlutil::locate(1 + x, y);
                rlutil::setChar('X');
            }
        }
    }
    rlutil::showcursor();
}

// void RendererConsole::printThis(char letter, int yCoord)
// {
//     // rlutil::locate(1, yCoord);
//     // rlutil::setChar(letter);
// }
