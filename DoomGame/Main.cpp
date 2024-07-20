#include <iostream>
#include "Game.h"
#include "Angle.h"


int main(int argc, char* args[])
{
	//Angle angle(0xC0000000);

	//Angle angle2(0x80000000);

	//Angle sum = angle + angle2;

	//std::cout << std::hex << sum.getAngle() << std::endl;

	try
	{
		Game game;
		game.init();
		while (!game.isOver())
		{
			game.processInput();
			game.update();
			game.render();
			game.delay();
		}
		return 0;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}

