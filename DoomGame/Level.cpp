#include "Level.h"

Level::Level(std::string name) : name(name), xMin(INT_MAX), xMax(INT_MIN), yMin(INT_MAX), yMax(INT_MIN), autoMapScaleFactor(15)
{

}

Level::~Level()
{

}

void Level::addVertex(const Vertex& vertex)
{
	vertexes.push_back(vertex);
	int16_t x = vertex.x;
	int16_t y = vertex.y;

	compareNumbers(xMax, xMin, x);
	compareNumbers(yMax, yMin, y);



}

void Level::compareNumbers(int& max, int& min, int16_t num)
{
	if (min > num)
	{
		min = num;
	}
	else if (max < num)
	{
		max = num;
	}
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

void Level::renderAutoMap(SDL_Renderer* pRenderer)
{
	int xShift = -xMin;
	int yShift = -yMin;

	int renderXSize;
	int renderYSize;

	SDL_RenderGetLogicalSize(pRenderer, &renderXSize, &renderYSize);

	--renderXSize;
	--renderYSize;

	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (Linedef& linedef : linedefs)
	{
		Vertex vertexStart = vertexes.at(linedef.startVertex);
		Vertex vertexEnd = vertexes.at(linedef.endVertex);

		SDL_RenderDrawLine(pRenderer,
			(vertexStart.x + xShift) / autoMapScaleFactor,
			renderYSize - (vertexStart.y + yShift) / autoMapScaleFactor,
			(vertexEnd.x + xShift) / autoMapScaleFactor,
			renderYSize - (vertexEnd.y + yShift) / autoMapScaleFactor);
	}
}

std::string Level::getName() const
{
	return name;
}