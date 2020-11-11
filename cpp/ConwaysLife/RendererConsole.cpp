#include "RendererConsole.hpp"

void RendererConsole::render(const LifeSimulator& simulation)
{
    rlutil::locate(1, 1);
    rlutil::setChar('X');
}

// void RendererConsole::printThis(char letter, int yCoord)
// {
//     // rlutil::locate(1, yCoord);
//     // rlutil::setChar(letter);
// }
