#include "Player.h"

Player::Player(int id) : playerID(id)
{

}

Player::~Player()
{
}

void Player::setXPosition(int xPosition)
{
	this->xPosition = xPosition;
}

void Player::setYPosition(int yPosition)
{
	this->yPosition = yPosition;
}

void Player::setAngle(int angle)
{
	this->angle = angle;
}

int Player::getID()
{
	return playerID;
}

int Player::getXPosition()
{
	return xPosition;
}

int Player::getYPosition()
{
	return yPosition;
}

int Player::getAngle()
{
	return angle;
}
