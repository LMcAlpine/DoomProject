#pragma once

#include <vector>
#include <string>

#include "DataTypes.h"
#include <SDL.h>
class Level
{
public:
	Level(std::string name);
	~Level();

	std::string getName() const;
	void addVertex(const Vertex& vertex);
	void compareNumbers(int& max, int& min, int16_t num);
	void addLinedef(const Linedef& linedef);
	void addNode(const Node& node);
	void addSidedef(const Sidedef& sidedef);
	void addSeg(const Seg& seg);
	void addSector(const Sector& sector);
	void addSubsector(const Subsector& subsector);

	void renderAutoMap(SDL_Renderer* pRenderer);
	void renderBSPNode(SDL_Renderer* pRenderer, int16_t bspNum);

	bool leftSide(int x, int y, int16_t nodeID);

	std::vector<Node> getNodes();



protected:
	std::string name;
	std::vector<Vertex> vertexes; // (vertices)
	std::vector<Linedef> linedefs;
	std::vector<Node> nodes{};
	std::vector<Sidedef> sidedefs{};
	std::vector<Seg> segs{};
	std::vector<Sector> sectors{};
	std::vector<Subsector> subsectors{};

	int xMin;
	int xMax;
	int yMin;
	int yMax;
	int autoMapScaleFactor;
};

