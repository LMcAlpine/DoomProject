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

	auto subsectors = level->getSubsectors();
	auto segs = level->getSegs();
	auto vertexes = level->getVertexes();
	std::string points = "(";
	for (int i = 0; i < subsectors.size(); i++)
	{
		if (i != 0)
		{
			points += "(";
		}
		for (int j = 0; j < subsectors.at(i).segCount; j++)
		{
			if (j != 0)
			{
				points += "(";
			}
			//std::cout << vertexes.at(segs.at((subsectors.at(i).firstSegNumber)).startingVertexNumber).x  << std::endl;
			int x = vertexes.at(segs.at((subsectors.at(i).firstSegNumber+j)).startingVertexNumber).x;
			points += std::to_string(x);
			points += ",";
			points += std::to_string(vertexes.at(segs.at((subsectors.at(i).firstSegNumber+j)).startingVertexNumber).y);
			points += "), ";

			//int x2 = vertexes.at(segs.at((subsectors.at(i).firstSegNumber)).startingVertexNumber).x;
		}
		
	}
	points.pop_back();
	points.pop_back();
	std::cout << points << std::endl;




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
