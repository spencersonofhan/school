#include "LifeSimulator.hpp"

void fill2DV(std::vector<std::vector<bool>>& grid, std::uint8_t x, std::uint8_t y);
void fill2DV(std::vector<std::vector<bool>>& newGrid, std::vector<std::vector<bool>>& theGrid, std::uint8_t nX, std::uint8_t nY);

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    LifeSimulator::X = sizeX;
    LifeSimulator::Y = sizeY;

    fill2DV(theGrid, X, Y);

    // Insert the patterns (seed)
    PatternAcorn acorn;
    PatternBlock block;
    PatternBlinker blinker;
    PatternGlider glider;
    PatternGosperGliderGun pggg;
    // This doesn't account for very small terminal windows
    insertPattern(pggg, 45, 19);
    insertPattern(block, 80, 8);
    insertPattern(blinker, 3, 14);
    insertPattern(glider, 0, 0);
    insertPattern(acorn, 60, 10);
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    auto pX = pattern.getSizeX();
    auto pY = pattern.getSizeY();

    for (decltype(pY) y = 0; y < pY; y++)
    {
        if (startY + y >= Y)
        {
            break;
        }
        for (decltype(pX) x = 0; x < pX; x++)
        {
            // Check if beyond boundaries
            if (startX + x >= X)
            {
                break;
            }
            theGrid[startY + y][startX + x] = pattern.getCell(x, y);
        }
    }
}

void LifeSimulator::update()
{
    // create 2D bool vector for new cells to be copied too
    std::vector<std::vector<bool>> newGrid;
    fill2DV(newGrid, theGrid, X, Y);

    uint8_t neighbors;
    // loops through all cells, counting each alive neighbors
    for (uint8_t y = 0; y < Y; y++)
    {
        for (uint8_t x = 0; x < X; x++)
        {
            neighbors = 0;
            bool isAlive = getCell(x, y);

            // Check for corner
            if (x == 0 && y == 0) // topleft
            {
                if (getCell(x + 1, y))
                {
                    neighbors++;
                }
                if (getCell(x, y + 1))
                {
                    neighbors++;
                }
                if (getCell(x + 1, y + 1))
                {
                    neighbors++;
                }
            }
            else if (x == X - 1 && y == 0) // topright
            {
                if (getCell(x - 1, y))
                {
                    neighbors++;
                }
                if (getCell(x - 1, y))
                {
                    neighbors++;
                }
                if (getCell(x, y + 1))
                {
                    neighbors++;
                }
            }
            else if (x == X - 1 && y == Y - 1) // bottomright
            {
                if (getCell(x - 1, y - 1))
                {
                    neighbors++;
                }
                if (getCell(x, y - 1))
                {
                    neighbors++;
                }
                if (getCell(x - 1, y))
                {
                    neighbors++;
                }
            }
            else if (x == X - 1 && y == Y - 1) // bottomleft
            {
                if (getCell(x, y - 1))
                {
                    neighbors++;
                }
                if (getCell(x + 1, y - 1))
                {
                    neighbors++;
                }
                if (getCell(x + 1, y))
                {
                    neighbors++;
                }
            }
            else // non-corners
            {
                if (x == 0) // left border
                {
                    if (getCell(x, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y))
                    {
                        neighbors++;
                    }
                    if (getCell(x, y + 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y + 1))
                    {
                        neighbors++;
                    }
                }
                else if (x == X - 1) // right border
                {
                    if (getCell(x - 1, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x - 1, y))
                    {
                        neighbors++;
                    }
                    if (getCell(x - 1, y + 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x, y + 1))
                    {
                        neighbors++;
                    }
                }
                else if (y == 0) // top border
                {
                    if (getCell(x - 1, y))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y))
                    {
                        neighbors++;
                    }
                    if (getCell(x - 1, y + 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x, y + 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y + 1))
                    {
                        neighbors++;
                    }
                }
                else if (y == Y - 1) // bottom border
                {
                    if (getCell(x - 1, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x - 1, y))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y))
                    {
                        neighbors++;
                    }
                }
                else // normal cell (everything else)
                {
                    if (getCell(x - 1, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y - 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x - 1, y))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y))
                    {
                        neighbors++;
                    }
                    if (getCell(x - 1, y + 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x, y + 1))
                    {
                        neighbors++;
                    }
                    if (getCell(x + 1, y + 1))
                    {
                        neighbors++;
                    }
                }
            }

            if (!isAlive && neighbors == 3)
            {
                newGrid[y][x] = true;
                continue;
            }

            if (isAlive)
            {
                if (neighbors == 2 || neighbors == 3)
                {
                    newGrid[y][x] = true;
                }
                else
                {
                    newGrid[y][x] = false;
                }
            }
        }
    }
    theGrid.swap(newGrid);
}

std::uint8_t LifeSimulator::getSizeX() const
{
    return X;
}
std::uint8_t LifeSimulator::getSizeY() const
{
    return Y;
}

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

// Overloaded for making a copy of theGrid
void fill2DV(std::vector<std::vector<bool>>& newGrid, std::vector<std::vector<bool>>& theGrid, std::uint8_t nX, std::uint8_t nY)
{
    for (uint8_t y = 0; y < nY; y++)
    {
        std::vector<bool> row(nX);
        for (uint8_t x = 0; x < nX; x++)
        {
            row[x] = theGrid[y][x];
        }
        newGrid.push_back(row);
    }
}
