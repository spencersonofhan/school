#include "LifeSimulator.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

#include <cstdint>
#include <memory>
#include <thread>

int main()
{
    auto r = rlutil::trows();
    auto c = rlutil::tcols() - 2;
    // cols - 2 makes accurate rendering possible

    uint8_t rows = static_cast<uint8_t>(r);
    uint8_t cols = static_cast<uint8_t>(c);

    std::shared_ptr<LifeSimulator> lifeSim = std::make_shared<LifeSimulator>(*(new LifeSimulator(cols, rows)));
    std::shared_ptr<RendererConsole> rConsole = std::make_shared<RendererConsole>(*(new RendererConsole()));

    // First rendering
    rlutil::cls();
    rConsole->render(*lifeSim);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Steps of evolution
    for (int step = 0; step < 1000; step++) // I chose a for loop instead of a while loop, while(true) loops make me unhappy
    {
        lifeSim->update();
        rConsole->render(*lifeSim);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
