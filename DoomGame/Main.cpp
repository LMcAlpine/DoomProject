// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include "WADReader.h"
#include "Game.h"


int main()
{


	try
	{

		Game game;
		game.init();
		while (!game.isOver())
		{
			game.processInput();
			game.update();
			game.render();
			game.delay();
		}

		Header header;
		DirectoryEntry directoryEntry;
		WADReader wadReader;
		//auto buffer = wadReader.readFileData("./DOOM.WAD");
		//int offset = 0;
		//wadReader.readHeader(buffer, header, offset);
		//wadReader.readDirectory(buffer, header, header.directoryOffset);




		//int index = wadReader.searchForLump("E1M1");
		//wadReader.readVertexes(buffer, index);
		//wadReader.readLinedefs(buffer, index);
		//wadReader.readNodes(buffer, index);
		//wadReader.readSidedefs(buffer, index);
		//wadReader.readSegs(buffer, index);
		//wadReader.readSectors(buffer, index);
		//wadReader.readSubsectors(buffer, index);
		return 0;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}

