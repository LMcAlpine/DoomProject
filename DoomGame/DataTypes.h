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

struct Sidedef
{
	int16_t xOffset{};
	int16_t yOffset{};
	char upperTextureName[8]{};
	char lowerTextureName[8]{};
	char middleTextureName[8]{};
	int16_t sectorNumber{};
};

struct Seg
{
	uint16_t startingVertexNumber{};
	uint16_t endingVertexNumber{};
	int16_t angle{};
	uint16_t linedefNumber{};
	uint16_t direction{};
	uint16_t offset{};
};

struct Sector
{
	int16_t floorHeight{};
	int16_t ceilingHeight{};
	char floorTextureName[8]{};
	char ceilingTextureName[8]{};
	uint16_t lightLevel{};
	uint16_t type{};
	uint16_t tagNumber{};
};

struct Subsector
{
	uint16_t segCount{};
	uint16_t firstSegNumber{};
};

struct Thing
{
	int16_t xPosition{};
	int16_t yPosition{};
	int16_t angle{};
	int16_t thingType{};
	int16_t flags{};
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