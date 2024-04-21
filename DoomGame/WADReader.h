#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream> 
#include <cstddef>
#include "DataTypes.h"
class WADReader
{
public:
	WADReader();

	std::vector<std::byte> readFileData(const std::string& name);

	void extractID(std::vector<std::byte>& buffer, Header &header);

	~WADReader();


};

