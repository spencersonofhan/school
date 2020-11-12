#pragma once

#include "Pattern.hpp"

class PatternGosperGliderGun : public Pattern
{
  public:
    virtual std::uint8_t getSizeX() const { return sizeX; }
    virtual std::uint8_t getSizeY() const { return sizeY; }
    virtual bool getCell(std::uint8_t x, std::uint8_t y) const;

  private:
    std::uint8_t sizeX = 36;
    std::uint8_t sizeY = 9;
};
