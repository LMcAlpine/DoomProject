#include "Level.h"

Level::Level(std::string name, SDL_Renderer* renderer, Player* player) : name(name), renderer(renderer), player(player), xMin(INT_MAX), xMax(INT_MIN), yMin(INT_MAX), yMax(INT_MIN), autoMapScaleFactor(15)
{
	SDL_RenderGetLogicalSize(renderer, &renderXSize, &renderYSize);
	--renderXSize;
	--renderYSize;
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

void Level::renderPlayerView()
{
	//renderPlayer();
	renderAutoMap();
	renderBSPNode(getNodes().size() - 1);


}

void Level::renderAutoMap()
{
	int xShift = -xMin;
	int yShift = -yMin;

	SDL_SetRenderDrawColor(renderer, 83, 83, 83, SDL_ALPHA_OPAQUE);
	for (Linedef& linedef : linedefs)
	{
		Vertex vertexStart = vertexes.at(linedef.startVertex);
		Vertex vertexEnd = vertexes.at(linedef.endVertex);

		SDL_RenderDrawLine(renderer,
			remapXToScreen(vertexStart.x),
			remapYToScreen(vertexStart.y),
			remapXToScreen(vertexEnd.x),
			remapYToScreen(vertexEnd.y));
	}
}


void Level::renderPlayer()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	std::pair<int, int> direction[] = {
		std::make_pair(-1, -1), std::make_pair(0, -1), std::make_pair(+1, -1),
		std::make_pair(-1, 0), std::make_pair(0, 0), std::make_pair(+1, 0),
		std::make_pair(-1, +1), std::make_pair(0, +1), std::make_pair(+1, +1)
	};

	for (int i = 0; i < 9; ++i)
	{
		SDL_RenderDrawPoint(renderer,
			remapXToScreen(player->getXPosition()) + direction[i].first,
			remapYToScreen(player->getYPosition()) + direction[i].second);
	}
}

int16_t Level::remapXToScreen(int16_t x)
{
	return (x + (-xMin)) / autoMapScaleFactor;
}

int16_t Level::remapYToScreen(int16_t y)
{
	return renderYSize - (y + (-yMin)) / autoMapScaleFactor;
}



void Level::renderBSPNode(int16_t bspNum)
{
	if (bspNum & 0x8000)
	{
		//renderSubsector(bspNum & (~0x8000));
		//int16_t subsectorID = bspNum & (~0x8000);
		//Subsector subsector = subsectors.at(subsectorID);
		//SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, SDL_ALPHA_OPAQUE);





		//for (int i = 0; i < subsector.segCount; i++)
		//{
		//	// draw segs
		//	Seg seg = segs[subsector.firstSegNumber + i];
		//	SDL_RenderDrawLine(renderer,
		//		remapXToScreen(vertexes.at(seg.startingVertexNumber).x),
		//		remapYToScreen(vertexes.at(seg.startingVertexNumber).y),
		//		remapXToScreen(vertexes.at(seg.endingVertexNumber).x),
		//		remapYToScreen(vertexes.at(seg.endingVertexNumber).y));

		//}
		//SDL_RenderPresent(renderer); 
		//SDL_Delay(100);
		return;
	}

	bool onLeft = leftSide(player->getXPosition(), player->getYPosition(), bspNum);


	Node bsp = nodes.at(bspNum);


	// draw the partition line in yellow for the root node division
	if (bspNum == 237)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, remapXToScreen(bsp.x), remapYToScreen(bsp.y), remapXToScreen(bsp.x + bsp.changeInX), remapYToScreen(bsp.y + bsp.changeInY));
	}
	

	//SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, SDL_ALPHA_OPAQUE);
	//if (bspNum == 237)
	//{
	//Node bsp2 = nodes.at(bspNum);
	//SDL_RenderDrawLine(renderer, remapXToScreen(bsp2.x), remapYToScreen(bsp2.y), remapXToScreen(bsp2.x + bsp2.changeInX), remapYToScreen(bsp2.y + bsp2.changeInY));
	//	SDL_RenderPresent(renderer); 
	   // SDL_Delay(100);
	//}


	if (onLeft)
	{
		renderBSPNode(bsp.rightChild);
		renderBSPNode(bsp.leftChild);
	}
	else
	{
		renderBSPNode(bsp.leftChild);
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
	Subsector subsector = subsectors.at(subsectorID);
	//SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < subsector.segCount; i++)
	{
		// draw segs
		Seg seg = segs[subsector.firstSegNumber + i];
		SDL_RenderDrawLine(renderer,
			remapXToScreen(vertexes.at(seg.startingVertexNumber).x),
			remapYToScreen(vertexes.at(seg.startingVertexNumber).y),
			remapXToScreen(vertexes.at(seg.endingVertexNumber).x),
			remapYToScreen(vertexes.at(seg.endingVertexNumber).y));

	}
	//SDL_RenderPresent(renderer); 
	//SDL_Delay(100);
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
