#pragma once
#include <cstdint>

struct Header
{
	char WADType[5]{};				// "IWAD" or "PWAD" 
	uint32_t numDirectories{};		// #lumps in directory
	uint32_t directoryOffset{};		// Offset to directory
};

struct DirectoryEntry
{
	uint32_t offset{};				// Offset to lump
	uint32_t size{};				// Size of the lump
	char name[8]{};					// Name of the lump
};
struct Vertex
{
	short x{};
	short y{};
};

enum LumpsIndex
{
	things = 1,
	linedefs,
	sidedefs,
	vertexes,
	segs,
	ssectors,
	nodes,
	sectors
};