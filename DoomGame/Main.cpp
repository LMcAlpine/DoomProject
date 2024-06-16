#include <iostream>
#include "Game.h"


int main(int argc, char* args[])
{
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

