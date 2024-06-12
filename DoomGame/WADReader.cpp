#include "WADReader.h"
WADReader::WADReader() {};

WADReader::~WADReader() {};


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

void WADReader::readVertexes(std::vector<std::byte>& buffer, int index)
{
	index += LumpsIndex::vertexes;
	DirectoryEntry vertexLump = directory.at(index);
	Vertex vertex;
	for (int i = 0; i < vertexLump.size / sizeof(Vertex); i++)
	{
		vertex.x = read2Bytes(buffer, vertexLump.offset);
		vertex.y = read2Bytes(buffer, vertexLump.offset + sizeof(uint16_t));
		vertexes.push_back(vertex);
		vertexLump.offset += sizeof(uint32_t);
	}
}

void WADReader::readLinedefs(std::vector<std::byte>& buffer, int index)
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
		linedefs.push_back(linedef);
		linedefsLump.offset += sizeof(Linedef);
	}
}

void WADReader::readNodes(std::vector<std::byte>& buffer, int index)
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
		nodes.push_back(node);
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

std::vector<Node> WADReader::getNodes()
{
	return std::vector<Node>();
}
