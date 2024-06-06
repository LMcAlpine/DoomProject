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

void WADReader::readDirectory(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, Header& header, uint32_t& offset)
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
	offset += 4;
}

void WADReader::extractNumDirectories(std::vector<std::byte>& buffer, Header& header, int& offset)
{
	header.numDirectories = read4Bytes(buffer, offset);
	offset += 4;
}

void WADReader::extractDirectoryOffset(std::vector<std::byte>& buffer, Header& header, int& offset)
{
	header.directoryOffset = read4Bytes(buffer, offset);
}

void WADReader::readLumpOffset(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset)
{
	directoryEntry.offset = read4Bytes(buffer, offset);
	offset += 4;

}

void WADReader::readLumpSize(std::vector<std::byte>& buffer, DirectoryEntry& directoryEntry, uint32_t& offset)
{
	directoryEntry.size = read4Bytes(buffer, offset);
	offset += 4;
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
}

void WADReader::readVertexes(std::vector<std::byte>& buffer, int index)
{
	DirectoryEntry vertexLump = directory.at(index + 4);
	Vertex vertex;
	for (int i = 0; i < vertexLump.size / sizeof(int); i++)
	{
		vertex.x = read2Bytes(buffer, vertexLump.offset);
		vertex.y = read2Bytes(buffer, vertexLump.offset + sizeof(short));
		vertexes.push_back(vertex);
		vertexLump.offset += sizeof(int);
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