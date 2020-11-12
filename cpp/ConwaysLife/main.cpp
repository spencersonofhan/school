#include "LifeSimulator.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

#include <cstdint>
#include <thread>
#include <memory>

int main() {
	// cols - 2 makes accurate rendering possible
	auto rows = rlutil::trows();
	auto cols = rlutil::tcols() - 2;

	std::shared_ptr<LifeSimulator> lifeSim = std::make_shared<LifeSimulator>(*(new LifeSimulator(cols, rows)));
	std::shared_ptr<RendererConsole> rConsole = std::make_shared<RendererConsole>(*(new RendererConsole()));

	// First rendering
	rlutil::cls();
	rConsole->render(*lifeSim);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// Steps of evolution
	for(int step = 0; step < 1000; step++)
	{
		lifeSim->update();
		rConsole->render(*lifeSim);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
