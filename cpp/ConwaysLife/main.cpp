#include "LifeSimulator.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"
#include "PatternAcorn.hpp"
#include "PatternBlock.hpp"
#include "PatternBlinker.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"

#include <iostream>
#include <cstdint>
#include <thread>
#include <memory>

int main() {
	// cols - 2 makes accurate rendering possible
	auto rows = rlutil::trows();
	auto cols = rlutil::tcols() - 2;

	std::shared_ptr<LifeSimulator> lifeSim = std::make_shared<LifeSimulator>(*(new LifeSimulator(cols, rows)));
	std::shared_ptr<RendererConsole> rConsole = std::make_shared<RendererConsole>(*(new RendererConsole()));

	// std::cout << "X: " << static_cast<int>(cols) << " Y: " << static_cast<int>(rows) << std::endl;
	// Insert the patterns
	PatternAcorn acorn;
	PatternBlock block;
	PatternBlinker blinker;
	PatternGlider glider;
	PatternGosperGliderGun pggg;
	lifeSim->insertPattern(pggg, 45, 19);
	lifeSim->insertPattern(block, 80, 8);
	lifeSim->insertPattern(blinker, 3, 14);
	lifeSim->insertPattern(acorn, 60, 10);


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
