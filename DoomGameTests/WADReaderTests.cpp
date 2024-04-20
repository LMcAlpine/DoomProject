#include "pch.h"
#include "../DoomGame/WADReader.h"
#include "../DoomGame/WADReader.cpp"

class WADReaderTests : public ::testing::Test {
protected:
	WADReader wadReader;
};



static TEST_F(WADReaderTests, HandleNonExistentFile) {
	std::string path = "./FAKE.WAD";
	EXPECT_THROW(wadReader.readFileData(path), std::runtime_error);
}
