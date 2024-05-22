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

	void extractID(std::vector<std::byte>& buffer, Header& header);

	void extractTotalLumps(std::vector<std::byte>& buffer, Header& header, int offset);

	uint16_t read2Bytes(std::vector<std::byte>& buffer, int offset);

	uint32_t read4Bytes(std::vector<std::byte>& buffer, int offset);

	~WADReader();


};

