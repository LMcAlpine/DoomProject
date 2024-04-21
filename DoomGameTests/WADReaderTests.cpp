#include "pch.h"
#include "../DoomGame/WADReader.h"
#include "../DoomGame/WADReader.cpp"
#include "../DoomGame/DataTypes.h"

class WADReaderTests : public ::testing::Test 
{
protected:
	WADReader wadReader;
	Header header;
};



static TEST_F(WADReaderTests, HandleNonExistentFile) 
{
	std::string path = "./FAKE.WAD";
	EXPECT_THROW(wadReader.readFileData(path), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleHeaderID) 
{
	auto buffer = wadReader.readFileData("./DOOM.WAD");
	Header header;
	wadReader.extractID(buffer, header);
	ASSERT_EQ(std::string(header.WADType), "IWAD");
}
