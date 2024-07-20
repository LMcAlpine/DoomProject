#include "Angle.h"
#include <SDL_stdinc.h>

constexpr int FRACBITS = 16;
constexpr Angle::Fixed FRACUNIT = 1 << FRACBITS;

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

Angle::Fixed Angle::floatToFixed(float f)
{
	return static_cast<Fixed>(f * FRACUNIT);
}

float Angle::fixedToFloat(Fixed f)
{
	return static_cast<float>(f) / FRACUNIT;
}

Angle::Fixed Angle::fixedMul(Fixed a, Fixed b)
{
	return ((int64_t)a * b) >> FRACBITS;
}

Angle::Fixed Angle::fixedDiv(Fixed a, Fixed b)
{
	if ((abs(a) >> 14) >= abs(b))
	{
		return (a ^ b) < 0 ? INT32_MIN : INT32_MAX;
	}
	return ((int64_t)a << FRACBITS) / b;
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
