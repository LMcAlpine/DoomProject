#pragma once
#include <cstdint>
class Angle
{
public:
	Angle(uint32_t angle);
	~Angle();

	Angle operator+(const Angle& other) const;
	Angle operator-(const Angle& other) const;

	uint32_t getAngle();

private:
	uint32_t angle{};
};

