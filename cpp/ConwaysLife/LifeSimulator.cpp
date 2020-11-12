#include "LifeSimulator.hpp"

void fill2DV(std::vector<std::vector<bool>>& grid, std::uint8_t x, std::uint8_t y);

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    LifeSimulator::X = sizeX;
    LifeSimulator::Y = sizeY;

    std::vector<std::vector<bool>> y;

    fill2DV(y, X, Y);

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
            if(pattern.getCell(x, y))
            {
                std::cout << "X: " << static_cast<int>(startX + x) << " Y: " << static_cast<int>(startY + y) << std::endl;
            }

            theGrid[startY+y][startX+x] = pattern.getCell(x, y);
            if(pattern.getCell(x, y))
            {
                std::cout << "SHOULD BE 1 -> " << theGrid[startY+y][startX+x] << std::endl;
            }

        }
    }
    std::cout << std::endl;
}

void LifeSimulator::update()
{
    // Create 2D bool vector for new cells to be copied too
    std::cout << theGrid[5][51] << std::endl;
    std::vector<std::vector<bool>> newGrid = theGrid;
    std::cout << theGrid[5][51] << std::endl;
    std::cout << newGrid[5][51] << std::endl;

    // fill2DV(newGrid, X, Y);
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
            switch(neighbors)
            {
                case 2: [[fallthrough]];
                case 3:
                    newGrid[y][x] = true;
                    break;
                case 0: [[fallthrough]];
                case 1: [[fallthrough]];
                case 4: [[fallthrough]];
                case 5: [[fallthrough]];
                case 6: [[fallthrough]];
                case 7: [[fallthrough]];
                case 8: [[fallthrough]];
                default:
                    newGrid[y][x] = false;
                    break;
            }
        }
    }
    theGrid.swap(newGrid);
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

void fill2DV(std::vector<std::vector<bool>>& grid, std::uint8_t nX, std::uint8_t nY)
{
    for (uint8_t i = 0; i < nY; i++)
	{
        std::vector<bool> x(nX);
		grid.push_back(x);
	}
}
