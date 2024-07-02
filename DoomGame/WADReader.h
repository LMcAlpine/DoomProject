#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream> 
#include <cstddef>
#include "DataTypes.h"
#include "Level.h"
class WADReader
{
	std::vector<DirectoryEntry> directory{};
	std::vector<std::byte> buffer{};

public:
	WADReader();
	std::vector<std::byte> readWAD(const std::string& name);

	std::vector<std::byte> readFileData(const std::string& name);

	void readHeader(std::vector<std::byte>& buffer, Header& header, int& offset);

	void readDirectory(std::vector<std::byte>& buffer, Header& header, uint32_t& offset);

	void extractID(std::vector<std::byte>& buffer, Header& header, int& offset);

	void extractNumDirectories(std::vector<std::byte>& buffer, Header& header, int& offset);

	void extractDirectoryOffset(std::vector<std::byte>& buffer, Header& header, int& offset);

	void readLumpOffset(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset);

	void readLumpSize(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset);

	void readLumpName(std::vector <std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset);

	int searchForLump(const std::string& name);

	void readLevelData(std::vector<std::byte> buffer, Level* level);

	void readVertexes(std::vector<std::byte>& buffer, int index, Level* level);

	void readLinedefs(std::vector<std::byte>& buffer, int index, Level* level);

	void readNodes(std::vector<std::byte>& buffer, int index, Level* level);

	void readBoundingBox(std::vector<std::byte>& buffer, BoundingBox& boundingBox, int offset);

	void readSidedefs(std::vector <std::byte>& buffer, int index, Level* level);

	void readTextureName(std::vector<std::byte>& buffer, char name[], int offset);

	void readSegs(std::vector<std::byte>& buffer, int index, Level* level);

	void readSectors(std::vector<std::byte>& buffer, int index, Level* level);

	void readSubsectors(std::vector<std::byte>& buffer, int index, Level* level);

	void readThings(std::vector<std::byte>& buffer, int index, Level* level);


	uint16_t read2Bytes(std::vector<std::byte>& buffer, int offset);

	uint32_t read4Bytes(std::vector<std::byte>& buffer, int offset);

	~WADReader();


};

