// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include "Game.h"


int main()
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

