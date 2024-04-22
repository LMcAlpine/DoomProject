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

void WADReader::extractID(std::vector<std::byte>& buffer, Header& header)
{
	for (int i = 0; i < 4; i++)
	{
		header.WADType[i] = (char)buffer.at(i);
	}

	header.WADType[4] = '\0';
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