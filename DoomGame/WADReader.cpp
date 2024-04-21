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

void WADReader::extractID(std::vector<std::byte>& buffer,Header &header)
{
	for (int i = 0; i < 4; i++)
	{
		header.WADType[i] = (char)buffer.at(i);
	}

	header.WADType[4] = '\0';
}