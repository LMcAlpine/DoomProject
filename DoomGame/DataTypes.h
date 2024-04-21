#pragma once
#include <cstdint>

struct Header
{
	char WADType[5];
	uint32_t directoryCount;
	uint32_t directoryOffset;
};