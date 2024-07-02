#include "Level.h"

Level::Level(std::string name, SDL_Renderer* renderer, Player* player) : name(name), renderer(renderer), player(player), xMin(INT_MAX), xMax(INT_MIN), yMin(INT_MAX), yMax(INT_MIN), autoMapScaleFactor(15)
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

void Level::addThing(const Thing& thing)
{
	things.push_back(thing);
}

void Level::renderAutoMap()
{
	int xShift = -xMin;
	int yShift = -yMin;

	int renderXSize;
	int renderYSize;

	SDL_RenderGetLogicalSize(renderer, &renderXSize, &renderYSize);

	--renderXSize;
	--renderYSize;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (Linedef& linedef : linedefs)
	{
		Vertex vertexStart = vertexes.at(linedef.startVertex);
		Vertex vertexEnd = vertexes.at(linedef.endVertex);

		SDL_RenderDrawLine(renderer,
			(vertexStart.x + xShift) / autoMapScaleFactor,
			renderYSize - (vertexStart.y + yShift) / autoMapScaleFactor,
			(vertexEnd.x + xShift) / autoMapScaleFactor,
			renderYSize - (vertexEnd.y + yShift) / autoMapScaleFactor);
	}
}

void Level::renderBSPNode(int16_t bspNum)
{
	int16_t i = bspNum & 0x8000;
	if (bspNum & 0x8000)
	{
		int16_t r = bspNum & (~0x8000);
		int r2 = r;
		renderSubsector(bspNum & (~0x8000));
	}

	bool onLeft = leftSide(player->getXPosition(), player->getYPosition(), bspNum);

	Node bsp;
	bsp = nodes.at(bspNum);
	if (onLeft)
	{
		renderBSPNode(bsp.leftChild);
	}
	else
	{
		renderBSPNode(bsp.rightChild);
	}


}

bool Level::leftSide(int x, int y, int16_t nodeID)
{
	int dx = x - nodes.at(nodeID).changeInX;
	int dy = y - nodes.at(nodeID).changeInY;
	return (((dx * nodes.at(nodeID).changeInY) - (dy * nodes.at(nodeID).changeInX)) <= 0);
}

void Level::renderSubsector(int16_t subsectorID)
{
}

std::vector<Node> Level::getNodes()
{
	return nodes;
}

Thing Level::getThings()
{
	return things.at(0);
}

std::string Level::getName() const
{
	return name;
}
