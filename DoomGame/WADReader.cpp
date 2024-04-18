#include "WADReader.h"
WADReader::WADReader() {};

WADReader::~WADReader() {};


// https://coniferproductions.com/posts/2022/10/25/reading-binary-files-cpp/
std::vector<std::byte> WADReader::readFileData(const std::string& name)
{
    std::filesystem::path inputFilePath{ name };
    auto length = std::filesystem::file_size(inputFilePath);
    if (length == 0) {
        return {}; // empty vector
    }
    std::vector<std::byte> buffer(length);
    std::ifstream inputFile(name, std::ios_base::binary);
    inputFile.read(reinterpret_cast<char*>(buffer.data()), length);
    inputFile.close();
    return buffer;
}