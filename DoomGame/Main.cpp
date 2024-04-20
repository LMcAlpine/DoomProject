// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WADReader.h"

int main()
{
	try
	{
		WADReader wadReader;
		wadReader.readFileData("./DOOM.WAD");
		return 0;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}

