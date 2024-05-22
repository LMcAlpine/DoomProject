#pragma once
#include <cstdint>

struct Header
{
	char WADType[5]{};
	uint32_t totalLumps{};
	uint32_t directoryOffset{};
};