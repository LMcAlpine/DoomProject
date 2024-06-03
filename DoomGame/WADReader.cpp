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
	// I began by trying to read just one lump. The very first one. 

	// I was mistakenly incrementing the offset for the lump name by 8 each time. So it did not get the right characters
	// The offset only needs to be incremented by one for each character in the name because the characters are stored next to each other in memory

	// Then I tried to read the first two lumps.
	// I realized I needed to create a new directory entry struct so as not to put the same thing in the vector. Might be able to reuse the struct?
	// but I think if I reused the struct then every single element will get updated to be the last added entry
	// Anyways, I thought to get to the next entry in the directory I had to increment the offset by 16 before reading the second lump
	// However, I determined I don't need to do this because as part of the process of reading the lump offset, lump size, and lump name, I was already incrementing
	// by 4, 4, and 8 to get 16. So after each new entry it will bring the offset to the correct location to read the next entry
	// Then I simply iterated through the number of directories in the header and that was how I got all the lump data from the WAD file

	// next I will need to see about the name of a lump being less than 8 bytes long, and null padding it to the right byte. 

	for (int i = 0; i < header.numDirectories; i++)
	{
		DirectoryEntry de;
		readLumpOffset(buffer, de, offset);
		readLumpSize(buffer, de, offset);
		readLumpName(buffer, de, offset);
		directory.push_back(de);
	}
	//readLumpOffset(buffer, directoryEntry, offset);
	//readLumpSize(buffer, directoryEntry, offset);
	//readLumpName(buffer, directoryEntry, offset);

	////offset += 16;
	//DirectoryEntry de;
	//readLumpOffset(buffer, de, offset);
	//readLumpSize(buffer, de, offset);
	//readLumpName(buffer, de, offset);
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