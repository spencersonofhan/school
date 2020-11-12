#include "LifeSimulator.hpp"

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    LifeSimulator::X = sizeX;
    LifeSimulator::Y = sizeY;

    std::vector<std::vector<bool>> y;

	for (uint8_t i = 0; i < sizeY; i++)
	{
        std::vector<bool> x(sizeX);
		y.push_back(x);
	}

    theGrid = y;
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    auto pX = pattern.getSizeX();
    auto pY = pattern.getSizeY();

    for (decltype(pY) y = 0; y < pY; y++)
    {
        for (decltype(pX) x = 0; x < pX; x++)
        {
            theGrid[startY+y][startX+x] = pattern.getCell(x, y);
        }
    }
}

void LifeSimulator::update()
{
    // Create 2D bool vector for new cells to be copied too
    std::vector<std::vector<bool>> newGrid;
    uint8_t neighbors;
    bool topBoundary = false;
    bool rightBoundary = false;
    bool bottomBoundary = false;
    bool leftBoundary = false;
    // loop checks if cell is alive, then will check its surrounding cells
    for (uint8_t y = 0; y < Y; y++)
    {
        for (uint8_t x = 0; x < X; x++)
        {
            neighbors = 0;
            topBoundary = false;
            rightBoundary = false;
            bottomBoundary = false;
            leftBoundary = false;

            // check if boundary
            if(x - 1 == 255) { leftBoundary = true; }
            if(y - 1 == 255) { topBoundary = true; }
            if(x + 1 >= X) { rightBoundary = true; }
            if(y + 1 >= Y) { bottomBoundary = true; }

            // count the living neighbors
            for(uint8_t nY = y - 1; nY <= y + 1; nY++)
            {
                if (nY == y - 1 && topBoundary) { continue; }
                if (nY == y + 1 && bottomBoundary) { continue; }

                if(!leftBoundary)
                {
                    if(getCell(x - 1, nY)) { neighbors++; }
                }

                if (!rightBoundary)
                {
                    if(getCell(x + 1, nY)) { neighbors++; }
                }

                if(nY != y)
                {
                    if(getCell(x, nY)) { neighbors++; }
                }
            }

            // Implement game rules for cells to live
        }
    }
}

std::uint8_t LifeSimulator::getSizeX() const { return X; }
std::uint8_t LifeSimulator::getSizeY() const { return Y; }


bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= X || y >= Y)
    {
        return false;
    }
    return theGrid[y][x];
}
