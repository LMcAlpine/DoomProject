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
	int16_t x{};
	int16_t y{};
};

struct Linedef
{
	uint16_t startVertex{};
	uint16_t endVertex{};
	uint16_t flags{};
	uint16_t specialType{};
	uint16_t sectorTag{};
	uint16_t rightSidedef{};
	int16_t leftSidedef{};
};


struct BoundingBox
{
	int16_t top;
	int16_t bottom;
	int16_t left;
	int16_t right;
};

struct Node
{
	int16_t x{};
	int16_t y{};
	int16_t changeInX{};
	int16_t changeInY{};
	BoundingBox rightBoundingBox{};
	BoundingBox leftBoundingBox{};
	int16_t rightChild{};
	int16_t leftChild{};
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