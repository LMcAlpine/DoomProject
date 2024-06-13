#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream> 
#include <cstddef>
#include "DataTypes.h"
class WADReader
{
	std::vector<DirectoryEntry> directory{};
	std::vector<Vertex> vertexes{};
	std::vector<Linedef> linedefs{};
	std::vector<Node> nodes{};
	std::vector<Sidedef> sidedefs{};
	std::vector<Seg> segs{};
	std::vector<Sector> sectors{};
	std::vector<Subsector> subsectors{};
public:
	WADReader();

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

	void readVertexes(std::vector<std::byte>& buffer, int index);

	void readLinedefs(std::vector<std::byte>& buffer, int index);

	void readNodes(std::vector<std::byte>& buffer, int index);

	void readBoundingBox(std::vector<std::byte>& buffer, BoundingBox& boundingBox, int offset);

	void readSidedefs(std::vector <std::byte>& buffer, int index);

	void readTextureName(std::vector<std::byte>& buffer, char name[], int offset);

	void readSegs(std::vector<std::byte>& buffer, int index);

	void readSectors(std::vector<std::byte>& buffer, int index);

	void readSubsectors(std::vector<std::byte>& buffer, int index);


	uint16_t read2Bytes(std::vector<std::byte>& buffer, int offset);

	uint32_t read4Bytes(std::vector<std::byte>& buffer, int offset);

	std::vector<Node> getNodes();

	~WADReader();


};

