#pragma once

#include <cstdint>

#include "LifeSimulator.hpp"

class Renderer
{
    public:
        virtual void render(const LifeSimulator& simulation) = 0;
};
