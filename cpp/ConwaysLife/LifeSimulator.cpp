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
    theGrid[1][1] = true;
}

std::uint8_t LifeSimulator::getSizeX() const { return X; }
std::uint8_t LifeSimulator::getSizeY() const { return Y; }


bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    return theGrid[y][x];
}
