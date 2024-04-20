#include "pch.h"
#include "../DoomGame/WADReader.h"
#include "../DoomGame/WADReader.cpp"

namespace WADReaderTests {
	TEST(WADReaderTest, HandleNonExistentFile) {
		std::string path = "./FAKE.WAD";
		WADReader reader;
		EXPECT_THROW({ std::vector<std::byte> data = reader.readFileData(path); }, std::runtime_error);
	}
}