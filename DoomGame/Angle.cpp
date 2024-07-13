#include "Angle.h"

Angle::Angle(uint32_t angle) : angle(angle)
{

}

Angle::~Angle()
{
}

Angle Angle::operator+(const Angle& other) const
{
	return  Angle(angle + other.angle);
}

Angle Angle::operator-(const Angle& other) const
{
	return Angle(angle - other.angle);
}

uint32_t Angle::getAngle()
{
	return angle;
}
