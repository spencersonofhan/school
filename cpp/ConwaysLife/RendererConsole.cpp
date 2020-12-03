#include "RendererConsole.hpp"

void RendererConsole::render(const LifeSimulator& simulation)
{
    uint8_t offsetX = 2;
    uint8_t offsetY = 1;
    rlutil::cls();
    rlutil::hidecursor();
    for (uint8_t y = 0; y < simulation.getSizeY(); y++)
    {
        for (uint8_t x = 0; x < simulation.getSizeX(); x++)
        {
            if (simulation.getCell(x, y))
            {
                rlutil::locate(offsetX + x, offsetY + y);
                rlutil::setChar('X');
            }
        }
    }
    rlutil::locate(0, 0);
    std::cout << std::flush;
}
