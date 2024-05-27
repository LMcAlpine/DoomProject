#pragma once
#include <cstdint>

struct Header
{
	char WADType[5]{};				// "IWAD" or "PWAD" 
	uint32_t numDirectories{};		// #lumps in directory
	uint32_t directoryOffset{};		// Offset to directory
};