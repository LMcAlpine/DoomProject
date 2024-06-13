#pragma once

#include <vector>
#include <string>

#include "DataTypes.h"
class Level
{
public:
	Level(std::string name);
	~Level();

	std::string getName() const;
	void addVertex(const Vertex& vertex);
	void addLinedef(const Linedef& linedef);

protected:
	std::string name;
	std::vector<Vertex> vertexes; // (vertices)
	std::vector<Linedef> linedefs;
	std::vector<Node> nodes{};
	std::vector<Sidedef> sidedefs{};
	std::vector<Seg> segs{};
	std::vector<Sector> sectors{};
	std::vector<Subsector> subsectors{};
};

