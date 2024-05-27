#include "pch.h"
#include "../DoomGame/WADReader.h"
#include "../DoomGame/WADReader.cpp"
#include "../DoomGame/DataTypes.h"

class WADReaderTests : public ::testing::Test
{
protected:
	WADReader wadReader;
	Header header{};
	int offset = 0;
};

static TEST_F(WADReaderTests, HandleNonExistentFile)
{
	std::string path = "./FAKE.WAD";
	EXPECT_THROW(wadReader.readFileData(path), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleHeaderID)
{
	auto buffer = wadReader.readFileData("./DOOM.WAD");
	wadReader.extractID(buffer, header, offset);
	ASSERT_EQ(std::string(header.WADType), "IWAD");
}

static TEST_F(WADReaderTests, HandleHeaderIDPWAD)
{
	auto buffer = wadReader.readFileData("./mytestmap.wad");
	wadReader.extractID(buffer, header, offset);
	ASSERT_EQ(std::string(header.WADType), "PWAD");
}

static TEST_F(WADReaderTests, HandleTotalLumps)
{
	auto buffer = wadReader.readFileData("./DOOM.WAD");
	offset += 4;
	wadReader.extractTotalLumps(buffer, header, offset);
	ASSERT_EQ(header.totalLumps, 2306);
}

static TEST_F(WADReaderTests, HandleRead2Bytes)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06} };
	// Expecting 513 because 0x0201 in little-endian is 0x01 at the LSB and 0x02 at the MSB and is the decimal representation
	ASSERT_EQ(wadReader.read2Bytes(buffer, 0), 513);
}

static TEST_F(WADReaderTests, HandleReadOutOfBounds2Bytes)
{
	std::vector<std::byte> buffer = { std::byte{0x01} };
	EXPECT_THROW(wadReader.read2Bytes(buffer, 0), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleOffsetOutOfBounds2Bytes)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06} };
	EXPECT_THROW(wadReader.read2Bytes(buffer, -1), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleOffsetOutOfBoundsGreater2Bytes)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03} };
	EXPECT_THROW(wadReader.read2Bytes(buffer, 4), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleOutOfBoundsEqual2Bytes)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02} };
	ASSERT_EQ(wadReader.read2Bytes(buffer, 0), 513);
}


static TEST_F(WADReaderTests, HandleRead4Bytes)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06} };
	// Expecting 67305985 because 0x04030201 in little-endian is the decimal representation
	ASSERT_EQ(wadReader.read4Bytes(buffer, 0), 67305985);
}

static TEST_F(WADReaderTests, HandleReadOutOfBounds)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02} };
	EXPECT_THROW(wadReader.read4Bytes(buffer, 0), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleOffsetOutOfBounds)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06} };
	EXPECT_THROW(wadReader.read4Bytes(buffer, -1), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleOffsetOutOfBoundsGreater)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06} };
	EXPECT_THROW(wadReader.read4Bytes(buffer, 7), std::runtime_error);
}

static TEST_F(WADReaderTests, HandleOutOfBoundsEqual)
{
	std::vector<std::byte> buffer = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04} };
	ASSERT_EQ(wadReader.read4Bytes(buffer, 0), 67305985);
}