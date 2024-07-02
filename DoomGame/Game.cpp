#include "Game.h"
#include <iostream>
#include <string>

Game::Game() : windowWidth(1280), windowHeight(800)
{
	
}

Game::~Game()
{
	delete doomEngine;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("MyDoomProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "SDL failed to create window! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "SDL failed to create renderer! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	doomEngine = new Engine(renderer);
	if (!doomEngine->init())
	{
		std::cout << doomEngine->getName() << " failed to initialize!" << std::endl;
		return false;
	}

	if (SDL_RenderSetLogicalSize(renderer, doomEngine->getRenderWidth(), doomEngine->getRenderHeight()) != 0)
	{
		std::cout << "SDL failed to set logical size! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			doomEngine->keyPressed(event);
			break;
		case SDL_KEYUP:
			doomEngine->keyReleased(event);
			break;
		case SDL_QUIT:
			doomEngine->quit();
			break;
		}
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
	doomEngine->render();
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	doomEngine->update();
}

bool Game::isOver()
{
	return doomEngine->isOver();
}

void Game::delay()
{
	SDL_Delay(doomEngine->getTimePerFrame());
}
