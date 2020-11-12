#include "LifeSimulator.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"
#include "PatternAcorn.hpp"

#include <iostream>
#include <cstdint>
#include <thread>
#include <memory>

int main() {
	auto rows = rlutil::trows();
	auto cols = rlutil::tcols();

	std::shared_ptr<LifeSimulator> lifeSim = std::make_shared<LifeSimulator>(*(new LifeSimulator(cols, rows)));
	std::shared_ptr<RendererConsole> rConsole = std::make_shared<RendererConsole>(*(new RendererConsole()));

	// Insert the patterns
	PatternAcorn acorn;
	lifeSim->insertPattern(acorn, 50, 10);


	// First rendering
	rlutil::cls();
	rConsole->render(*lifeSim);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// Steps of evolution
	for(int step = 0; step < 1000; step++)
	{
		lifeSim->update();
		rConsole->render(*lifeSim);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}




	// std::cout << lifeSim->getCell(30, 120) << std::endl;


	// for (uint8_t i = 0; i < 10; i++)
	// {
	// 	for (uint8_t j = 0; j < 10; j++)
	// 	{
	// 		if (lifeSim->getCell(i, j))
	// 		{
	// 			std::cout << static_cast<int>(i) << " " << static_cast<int>(j) << std::endl;
	// 		}
	// 	}
	// }




	// Initially clear the screen
	// rlutil::cls();

	// std::vector<std::vector<bool>> grid(30)

	// for (int i = 0; i < 500; i++)
	// {
	// 	rConsole->render(*lifeSim);
	// 	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	// }



	// std::cout << lifeSim.getSizeX()  << std::endl << lifeSim.getSizeY() << std::endl;
}
