#include "WADReader.h"
#include <cstring>


WADReader::WADReader() {}


WADReader::~WADReader() {};

std::vector<std::byte> WADReader::readWAD(const std::string& name)
{
	buffer = readFileData(name);
	Header header;
	DirectoryEntry directoryEntry;
	int offset = 0;
	readHeader(buffer, header, offset);
	readDirectory(buffer, header, header.directoryOffset);
	return buffer;
};


// https://coniferproductions.com/posts/2022/10/25/reading-binary-files-cpp/
std::vector<std::byte> WADReader::readFileData(const std::string& name)
{
	std::filesystem::path inputFilePath{ name };

	if (!std::filesystem::exists(inputFilePath))
	{
		throw std::runtime_error("File does not exist: " + name);
	}

	auto length = std::filesystem::file_size(inputFilePath);
	if (length == 0)
	{
		return {}; // empty vector
	}
	std::vector<std::byte> buffer(length);
	std::ifstream inputFile(name, std::ios_base::binary);

	inputFile.read(reinterpret_cast<char*>(buffer.data()), length);

	inputFile.close();
	return buffer;
}

void WADReader::readHeader(std::vector<std::byte>& buffer, Header& header, int& offset)
{
	extractID(buffer, header, offset);
	extractNumDirectories(buffer, header, offset);
	extractDirectoryOffset(buffer, header, offset);
}

void WADReader::readDirectory(std::vector<std::byte>& buffer, Header& header, uint32_t& offset)
{
	DirectoryEntry de;
	for (int i = 0; i < header.numDirectories; i++)
	{
		readLumpOffset(buffer, de, offset);
		readLumpSize(buffer, de, offset);
		readLumpName(buffer, de, offset);
		directory.push_back(de);
	}
}

void WADReader::extractID(std::vector<std::byte>& buffer, Header& header, int& offset)
{
	for (int i = 0; i < 4; i++)
	{
		header.WADType[i] = (char)buffer.at(i);
	}

	header.WADType[4] = '\0';
	offset += sizeof(uint32_t);
}

void WADReader::extractNumDirectories(std::vector<std::byte>& buffer, Header& header, int& offset)
{
	header.numDirectories = read4Bytes(buffer, offset);
	offset += sizeof(uint32_t);
}

void WADReader::extractDirectoryOffset(std::vector<std::byte>& buffer, Header& header, int& offset)
{
	header.directoryOffset = read4Bytes(buffer, offset);
}

void WADReader::readLumpOffset(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset)
{
	directoryEntry.offset = read4Bytes(buffer, offset);
	offset += sizeof(uint32_t);

}

void WADReader::readLumpSize(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset)
{
	directoryEntry.size = read4Bytes(buffer, offset);
	offset += sizeof(uint32_t);
}

void WADReader::readLumpName(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset)
{
	for (int i = 0; i < 8; i++)
	{
		directoryEntry.name[i] = (char)buffer.at(offset++);
	}
}

int WADReader::searchForLump(const std::string& name)
{

	for (int i = 0; i < directory.size(); i++)
	{
		if (std::string(directory.at(i).name) == name)
		{
			return i;
		}
	}
	return -1;
}

void WADReader::readLevelData(std::vector<std::byte> buffer, Level* level)
{
	int index = searchForLump(level->getName());
	readVertexes(buffer, index, level);
	readLinedefs(buffer, index, level);
	readNodes(buffer, index, level);
	readSidedefs(buffer, index, level);
	readSegs(buffer, index, level);
	readSectors(buffer, index, level);
	readSubsectors(buffer, index, level);
}

void WADReader::readVertexes(std::vector<std::byte>& buffer, int index, Level* level)
{
	index += LumpsIndex::vertexes;
	DirectoryEntry vertexLump = directory.at(index);
	Vertex vertex;
	for (int i = 0; i < vertexLump.size / sizeof(Vertex); i++)
	{
		vertex.x = read2Bytes(buffer, vertexLump.offset);
		vertex.y = read2Bytes(buffer, vertexLump.offset + sizeof(uint16_t));
		level->addVertex(vertex);
		vertexLump.offset += sizeof(uint32_t);
	}
}

void WADReader::readLinedefs(std::vector<std::byte>& buffer, int index, Level* level)
{
	index += LumpsIndex::linedefs;
	DirectoryEntry linedefsLump = directory.at(index);
	Linedef linedef;
	for (int i = 0; i < linedefsLump.size / sizeof(Linedef); i++)
	{
		linedef.startVertex = read2Bytes(buffer, linedefsLump.offset);
		linedef.endVertex = read2Bytes(buffer, linedefsLump.offset + sizeof(uint16_t));
		linedef.flags = read2Bytes(buffer, linedefsLump.offset + (2 * sizeof(uint16_t)));
		linedef.specialType = read2Bytes(buffer, linedefsLump.offset + (3 * sizeof(uint16_t)));
		linedef.sectorTag = read2Bytes(buffer, linedefsLump.offset + (4 * sizeof(uint16_t)));
		linedef.rightSidedef = read2Bytes(buffer, linedefsLump.offset + (5 * sizeof(uint16_t)));
		linedef.leftSidedef = read2Bytes(buffer, linedefsLump.offset + (6 * sizeof(uint16_t)));
		level->addLinedef(linedef);
		linedefsLump.offset += sizeof(Linedef);
	}
}

void WADReader::readNodes(std::vector<std::byte>& buffer, int index, Level* level)
{
	index += LumpsIndex::nodes;
	DirectoryEntry nodesLump = directory.at(index);
	Node node;

	for (int i = 0; i < nodesLump.size / sizeof(Node); i++)
	{
		node.x = read2Bytes(buffer, nodesLump.offset);
		node.y = read2Bytes(buffer, nodesLump.offset + sizeof(uint16_t));
		node.changeInX = read2Bytes(buffer, nodesLump.offset + (2 * sizeof(uint16_t)));
		node.changeInY = read2Bytes(buffer, nodesLump.offset + (3 * sizeof(uint16_t)));
		readBoundingBox(buffer, node.rightBoundingBox, nodesLump.offset + (4 * sizeof(uint16_t)));
		readBoundingBox(buffer, node.leftBoundingBox, nodesLump.offset + (8 * sizeof(uint16_t)));
		node.rightChild = read2Bytes(buffer, nodesLump.offset + (12 * sizeof(uint16_t)));
		node.leftChild = read2Bytes(buffer, nodesLump.offset + (13 * (sizeof(uint16_t))));
		level->addNode(node);
		nodesLump.offset += sizeof(Node);

	}
}

void WADReader::readBoundingBox(std::vector<std::byte>& buffer, BoundingBox& boundingBox, int offset)
{
	boundingBox.top = read2Bytes(buffer, offset);
	boundingBox.bottom = read2Bytes(buffer, offset + 2);
	boundingBox.left = read2Bytes(buffer, offset + 4);
	boundingBox.right = read2Bytes(buffer, offset + 6);
}

void WADReader::readSidedefs(std::vector<std::byte>& buffer, int index, Level* level)
{
	index += LumpsIndex::sidedefs;
	DirectoryEntry sidedefsLump = directory.at(index);
	Sidedef sidedef;

	for (int i = 0; i < sidedefsLump.size / sizeof(Sidedef); i++)
	{
		sidedef.xOffset = read2Bytes(buffer, sidedefsLump.offset);
		sidedef.yOffset = read2Bytes(buffer, sidedefsLump.offset + sizeof(uint16_t));
		readTextureName(buffer, sidedef.upperTextureName, sidedefsLump.offset + 4);
		readTextureName(buffer, sidedef.lowerTextureName, sidedefsLump.offset + 12);
		readTextureName(buffer, sidedef.middleTextureName, sidedefsLump.offset + 20);
		sidedef.sectorNumber = read2Bytes(buffer, sidedefsLump.offset + 28);
		level->addSidedef(sidedef);
		sidedefsLump.offset += sizeof(Sidedef);

	}
}

void WADReader::readTextureName(std::vector<std::byte>& buffer, char name[], int offset)
{
	for (int j = 0; j < 8; j++)
	{
		name[j] = (char)buffer.at(offset++);
	}
}

void WADReader::readSegs(std::vector<std::byte>& buffer, int index, Level* level)
{
	index += LumpsIndex::segs;
	DirectoryEntry segsLump = directory.at(index);
	Seg seg;
	for (int i = 0; i < segsLump.size / sizeof(Seg); i++)
	{
		seg.startingVertexNumber = read2Bytes(buffer, segsLump.offset);
		seg.endingVertexNumber = read2Bytes(buffer, segsLump.offset + 2);
		seg.angle = read2Bytes(buffer, segsLump.offset + 4);
		seg.linedefNumber = read2Bytes(buffer, segsLump.offset + 6);
		seg.direction = read2Bytes(buffer, segsLump.offset + 8);
		seg.offset = read2Bytes(buffer, segsLump.offset + 10);
		level->addSeg(seg);
		segsLump.offset += sizeof(Seg);
	}
}

void WADReader::readSectors(std::vector<std::byte>& buffer, int index, Level* level)
{
	index += LumpsIndex::sectors;
	DirectoryEntry sectorsLump = directory.at(index);
	Sector sector;
	for (int i = 0; i < sectorsLump.size / sizeof(Sector); i++)
	{
		sector.floorHeight = read2Bytes(buffer, sectorsLump.offset);
		sector.ceilingHeight = read2Bytes(buffer, sectorsLump.offset + 2);
		readTextureName(buffer, sector.floorTextureName, sectorsLump.offset + 4);
		readTextureName(buffer, sector.ceilingTextureName, sectorsLump.offset + 12);
		sector.lightLevel = read2Bytes(buffer, sectorsLump.offset + 20);
		sector.type = read2Bytes(buffer, sectorsLump.offset + 22);
		sector.tagNumber = read2Bytes(buffer, sectorsLump.offset + 24);
		level->addSector(sector);
		sectorsLump.offset += sizeof(Sector);

	}
}

void WADReader::readSubsectors(std::vector<std::byte>& buffer, int index, Level* level)
{
	index += LumpsIndex::ssectors;
	DirectoryEntry subsectorsLump = directory.at(index);
	Subsector subsector;
	for (int i = 0; i < subsectorsLump.size / sizeof(Subsector); i++)
	{
		subsector.segCount = read2Bytes(buffer, subsectorsLump.offset);
		subsector.firstSegNumber = read2Bytes(buffer, subsectorsLump.offset + 2);
		level->addSubsector(subsector);
		subsectorsLump.offset += sizeof(Subsector);
	}
}


uint16_t WADReader::read2Bytes(std::vector<std::byte>& buffer, int offset)
{
	if (offset < 0 || buffer.size() < offset + sizeof(uint16_t))
	{
		throw std::runtime_error("Buffer overflow prevented. Buffer size: " + std::to_string(buffer.size()) + ", Required size from offset: " + std::to_string(offset + sizeof(uint16_t)));
	}
	uint16_t value;
	std::memcpy(&value, buffer.data() + offset, sizeof(uint16_t));
	return value;
}

uint32_t WADReader::read4Bytes(std::vector<std::byte>& buffer, int offset)
{
	if (offset < 0 || buffer.size() < offset + sizeof(uint32_t))
	{
		throw std::runtime_error("Buffer overflow prevented. Buffer size: " + std::to_string(buffer.size()) + ", Required size from offset: " + std::to_string(offset + sizeof(uint32_t)));
	}
	uint32_t value;
	std::memcpy(&value, buffer.data() + offset, sizeof(uint32_t));
	return value;
}
