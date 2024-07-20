#pragma once

#include <SDL.h>
class Player
{
public:
	Player(int id);
	~Player();

	void setXPosition(int16_t xPosition);
	void setYPosition(int16_t yPosition);
	void setAngle(int16_t angle);

	int getID();
	int16_t getXPosition();
	int16_t getYPosition();
	uint32_t getAngle();

protected:
	int playerID{};
	int16_t xPosition{};
	int16_t yPosition{};
	int16_t angle{};
};

