#pragma once

#include "LifeSimulator.hpp"

#include <cstdint>

class Renderer
{
  public:
    virtual void render(const LifeSimulator& simulation) = 0;
};
