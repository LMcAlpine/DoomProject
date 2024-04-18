// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WADReader.h"

int main()
{
    WADReader wadReader;
    wadReader.readFileData("./DOOM.WAD");
    return 0;
}

