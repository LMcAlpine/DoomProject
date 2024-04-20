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

	std::string extractID(std::vector<std::byte>& buffer);

	~WADReader();


};

