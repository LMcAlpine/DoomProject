#pragma once

#include <SDL.h>
#include "Engine.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void processInput();
	void render();
	void update();
	void delay();
	bool isOver();
	bool init();

protected:
	int windowWidth{};
	int windowHeight{};
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	Engine* doomEngine{};
};
