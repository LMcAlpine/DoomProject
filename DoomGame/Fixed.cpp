#include "Fixed.h"
#include <stdlib.h>


constexpr int FRACBITS = 16;
constexpr Fixed::fixed_t FRACUNIT = 1 << FRACBITS;



Fixed::Fixed() 
{

}


Fixed::~Fixed()
{
}


Fixed::fixed_t Fixed::floatToFixed(float f)
{
	return static_cast<fixed_t>(f * FRACUNIT);
}

float Fixed::fixedToFloat(fixed_t f)
{
	return static_cast<float>(f) / FRACUNIT;
}

Fixed::fixed_t Fixed::fixedMul(fixed_t a, fixed_t b)
{
	return ((int64_t)a * b) >> FRACBITS;
}

Fixed::fixed_t Fixed::fixedDiv(fixed_t a, fixed_t b)
{
	if ((abs(a) >> 14) >= abs(b))
	{
		return (a ^ b) < 0 ? INT32_MIN : INT32_MAX;
	}
	return ((int64_t)a << FRACBITS) / b;
}