// Engine.cpp
#include "Engine.h"

Engine::Engine() : isGameOver(false), renderWidth(320), renderHeight(200)
{
	level = new Level("E1M1");

}

Engine::~Engine()
{
	delete level;
	delete player;
}

bool Engine::init()
{
	auto buffer = wadReader.readWAD("./DOOM.WAD");
	wadReader.readLevelData(buffer, level);
	Thing thing = level->getThings();
	player = new Player(0);
	player->setXPosition(thing.xPosition);
	player->setYPosition(thing.yPosition);
	player->setAngle(thing.angle);
	return true;
}

void Engine::render(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(pRenderer);
	level->renderAutoMap(pRenderer);
	level->renderBSPNode(pRenderer, level->getNodes().size()-1,player->getXPosition(),player->getYPosition());
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
