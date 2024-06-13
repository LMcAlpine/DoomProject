#pragma once

#include <SDL.h>
#include <string>
#include "WADReader.h"
#include "Level.h"
class Engine
{
public:
	Engine();
	~Engine();

	virtual void render(SDL_Renderer* pRenderer); // Draw something to show on screen
	virtual void keyPressed(SDL_Event& event); // Which keys are pressed?
	virtual void keyReleased(SDL_Event& event); // Which keys are released?
	virtual void quit(); // Close and shutdown the game
	virtual void update();

	virtual bool isOver(); // Did the game end?
	virtual bool init(); // Initialize game object

	virtual int getRenderWidth();
	virtual int getRenderHeight();
	virtual int getTimePerFrame();

	virtual std::string getName();
	virtual std::string getWADFileName();

protected:
	int renderWidth;
	int renderHeight;

	bool isGameOver;

	WADReader wadReader;
	Level* level;

};

