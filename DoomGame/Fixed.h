#pragma once
#include <cstdint>
class Fixed
{
public:
	using fixed_t = int32_t;

	fixed_t floatToFixed(float f);
	float fixedToFloat(fixed_t f);

	fixed_t fixedMul(fixed_t a, fixed_t b);
	fixed_t fixedDiv(fixed_t a, fixed_t b);
};