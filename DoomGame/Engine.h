#pragma once

#include <SDL.h>
#include <string>
#include "WADReader.h"
#include "Level.h"
#include "Player.h"
class Engine
{
public:
	Engine(SDL_Renderer* renderer);
	~Engine();

	virtual void render();
	virtual void keyPressed(SDL_Event& event);
	virtual void keyReleased(SDL_Event& event);
	virtual void quit();
	virtual void update();

	virtual bool isOver();
	virtual bool init();

	virtual int getRenderWidth();
	virtual int getRenderHeight();
	virtual int getTimePerFrame();

	virtual std::string getName();
	virtual std::string getWADFileName();

protected:
	int renderWidth{};
	int renderHeight{};

	bool isGameOver{};

	SDL_Renderer* renderer{};
	WADReader wadReader{};
	Level* level{};
	Player* player{};

};

