#pragma once
#include <cstdint>
#include <math.h>


class Angle
{
public:
	Angle(uint32_t angle);
	Angle(double radians);
	~Angle();

	using Fixed = int32_t;

	Angle operator+(const Angle& other) const;
	Angle operator-(const Angle& other) const;

	Angle& operator-=(const unsigned int& other);

	Fixed floatToFixed(float f);
	float fixedToFloat(Fixed f);

	Fixed fixedMul(Fixed a, Fixed b);
	Fixed fixedDiv(Fixed a, Fixed b);

	static Angle fromRadians(double radians);
	double toRadians() const;
	double toDegrees() const;

	bool operator>=(const Angle& other);

	bool operator>=(const unsigned int& other);


	uint32_t getAngle();
private:
	uint32_t angle{};
	static constexpr uint32_t FULL_CIRCLE = 0xFFFFFFFF;

	

	
};

