// Engine.cpp
#include "Engine.h"

Engine::Engine(SDL_Renderer* renderer) : renderer(renderer), isGameOver(false), renderWidth(320), renderHeight(200)
{


}

Engine::~Engine()
{
	delete level;
	delete player;
}

bool Engine::init()
{
	player = new Player(0);
	level = new Level("E1M1", renderer, player);
	auto buffer = wadReader.readWAD("./DOOM.WAD");
	wadReader.readLevelData(buffer, level);
	Thing thing = level->getThings();
	player->setXPosition(thing.xPosition);
	player->setYPosition(thing.yPosition);
	player->setAngle(thing.angle);
	return true;
}

void Engine::render()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	level->renderPlayerView();
}

void Engine::keyPressed(SDL_Event& event)
{
}

void Engine::keyReleased(SDL_Event& event)
{
}

void Engine::quit()
{
	isGameOver = true;
}

void Engine::update()
{
}

bool Engine::isOver()
{
	return isGameOver;
}

int Engine::getRenderWidth()
{
	return renderWidth;
}

int Engine::getRenderHeight()
{
	return renderHeight;
}

int Engine::getTimePerFrame()
{
	return 1000 / 60;
}

std::string Engine::getName()
{
	return "MyDoomProject";
}

std::string Engine::getWADFileName()
{
	return std::string();
}
