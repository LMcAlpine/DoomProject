#include "Player.h"

Player::Player(int id) : playerID(id)
{

}

Player::~Player()
{
}

void Player::setXPosition(int16_t xPosition)
{
	this->xPosition = xPosition;
}

void Player::setYPosition(int16_t yPosition)
{
	this->yPosition = yPosition;
}

void Player::setAngle(int16_t angle)
{
	this->angle = angle;
}

int Player::getID()
{
	return playerID;
}

int16_t Player::getXPosition()
{
	return xPosition;
}

int16_t Player::getYPosition()
{
	return yPosition;
}

int16_t Player::getAngle()
{
	return angle;
}
