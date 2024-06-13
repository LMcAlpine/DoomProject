#include "Level.h"

Level::Level(std::string name) : name(name)
{

}

Level::~Level()
{

}

void Level::addVertex(const Vertex& vertex)
{
	vertexes.push_back(vertex);
}

void Level::addLinedef(const Linedef& linedef)
{
	linedefs.push_back(linedef);
}

void Level::addNode(const Node& node)
{
	nodes.push_back(node);
}

void Level::addSidedef(const Sidedef& sidedef)
{
	sidedefs.push_back(sidedef);
}

void Level::addSeg(const Seg& seg)
{
	segs.push_back(seg);
}

void Level::addSector(const Sector& sector)
{
	sectors.push_back(sector);
}

void Level::addSubsector(const Subsector& subsector)
{
	subsectors.push_back(subsector);
}

std::string Level::getName() const
{
	return name;
}