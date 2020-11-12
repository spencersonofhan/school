#pragma once

#include "Pattern.hpp"

#include <cstdint>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>


class LifeSimulator
{
    public:
        LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY);

        void insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY);
        void update();

        std::uint8_t getSizeX() const;
        std::uint8_t getSizeY() const;
        bool getCell(std::uint8_t x, std::uint8_t y) const;

    private:
        std::uint8_t X;
        std::uint8_t Y;

        std::vector<std::vector<bool>> theGrid;
};
