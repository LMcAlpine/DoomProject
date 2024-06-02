// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WADReader.h"

int main()
{
	try
	{
		Header header;
		DirectoryEntry directoryEntry;
		WADReader wadReader;
		auto buffer = wadReader.readFileData("./DOOM.WAD");
		int offset = 0;
		wadReader.readHeader(buffer, header, offset);
		wadReader.readDirectory(buffer, directoryEntry, header.directoryOffset);
		return 0;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}

