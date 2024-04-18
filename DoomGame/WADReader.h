#pragma once
#include <filesystem>
#include <vector>
#include <fstream> 
#include <cstddef>
class WADReader
{
public:
	WADReader();

	std::vector<std::byte> readFileData(const std::string& name);

	~WADReader();
};

