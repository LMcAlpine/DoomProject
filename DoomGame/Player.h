#pragma once

#include <SDL.h>
class Player
{
public:
	/*Player(int id, int16_t xPosition, int16_t yPosition, int16_t angle);*/
	Player(int id);
	~Player();

	void update();

	void setXPosition(int16_t xPosition);
	void setYPosition(int16_t yPosition);
	void setAngle(int16_t angle);

	int getID();
	int16_t getXPosition();
	int16_t getYPosition();
	int16_t getAngle();

protected:
	int playerID{};
	int16_t xPosition{};
	int16_t yPosition{};
	int16_t angle{};
};

