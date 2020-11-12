#include "RendererConsole.hpp"

void RendererConsole::render(const LifeSimulator& simulation)
{
    uint8_t offset = 2;
    rlutil::cls();
    rlutil::hidecursor();
    for(uint8_t y = 0; y < simulation.getSizeY(); y++)
    {
        for(uint8_t x = 0; x < simulation.getSizeX(); x++)
        {
            if (simulation.getCell(x, y))
            {
                rlutil::locate(offset + x, offset + y);
                rlutil::setChar('X');
            }
        }
    }
    rlutil::locate(simulation.getSizeX(), simulation.getSizeY());
    std::cout << std::flush;
}
