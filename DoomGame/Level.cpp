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

std::string Level::getName() const
{
	return name;
}