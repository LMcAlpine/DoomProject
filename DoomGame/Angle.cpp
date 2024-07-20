#include "Angle.h"
#include <SDL_stdinc.h>



Angle::Angle(uint32_t angle) : angle(angle)
{

}

Angle::Angle(double radians)
{
	angle = static_cast<uint32_t>((radians / (2 * M_PI)) * FULL_CIRCLE);
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

Angle& Angle::operator-=(const unsigned int& other)
{

	angle -= other;
	return *this;
}


bool Angle::operator>=(const Angle& other)
{
	return (angle >= other.angle);;
}

bool Angle::operator>=(const unsigned int& other)
{
	return (angle >= other);;
}

Angle Angle::fromRadians(double radians)
{
	return Angle(radians);
}

double Angle::toRadians() const
{
	return (static_cast<double>(angle) / FULL_CIRCLE) * 2 * M_PI;
}

double Angle::toDegrees() const
{
	return toRadians() * 180 / M_PI;
}

uint32_t Angle::getAngle()
{
	return angle;
}
