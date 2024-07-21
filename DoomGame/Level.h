#pragma once

#include <vector>
#include <string>

#include "DataTypes.h"
#include "Player.h"
#include "Angle.h"
#include <SDL.h>
class Level
{
public:
	Level(std::string name, SDL_Renderer* renderer, Player* player);
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

	void addThing(const Thing& thing);


	void renderPlayerView();
	void renderAutoMap();
	void renderPlayer();
	void renderBSPNode(int16_t bspNum);

	bool leftSide(int x, int y, int16_t nodeID);
	void renderSubsector(int16_t subsectorID);

	std::vector<Node> getNodes();
	Thing getThings();
	std::vector<Subsector> getSubsectors();
	std::vector<Vertex> getVertexes();
	std::vector<Seg> getSegs();

	int16_t remapXToScreen(int16_t x);
	int16_t remapYToScreen(int16_t y);





protected:
	std::string name;
	std::vector<Vertex> vertexes; // (vertices)
	std::vector<Linedef> linedefs;
	std::vector<Node> nodes{};
	std::vector<Sidedef> sidedefs{};
	std::vector<Seg> segs{};
	std::vector<Sector> sectors{};
	std::vector<Subsector> subsectors{};
	std::vector<Thing> things{};


	int xMin;
	int xMax;
	int yMin;
	int yMax;
	int renderXSize{};
	int renderYSize{};
	int autoMapScaleFactor;


	SDL_Renderer* renderer;
	Player* player{};


};

