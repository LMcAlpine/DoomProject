#pragma once

#include <SDL.h>
class Player
{
public:
	Player(int id);
	~Player();

	void setXPosition(int xPosition);
	void setYPosition(int yPosition);
	void setAngle(int angle);

	int getID();
	int getXPosition();
	int getYPosition();
	int getAngle();

protected:
	int playerID{};
	int xPosition{};
	int yPosition{};
	int angle{};

	SDL_Renderer* renderer{};
	Level* level{};
};

