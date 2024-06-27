#include "pch.h"
#include <cstdlib>
#include "../DoomGame/Level.h"
#include "../DoomGame/Level.cpp"
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

std::string getWadFilePath(const std::string &envVar)
{
	const char *wadPath = std::getenv(envVar.c_str());
	if (wadPath)
	{
		return std::string(wadPath);
	}
	else
	{
		throw std::runtime_error("Environment variable " + envVar + " is not set");
	}
}

TEST_F(WADReaderTests, HandleNonExistentFile)
{
	std::string path = "./FAKE.WAD";
	EXPECT_THROW(wadReader.readFileData(path), std::runtime_error);
}

TEST_F(WADReaderTests, HandleHeaderID)
{
	if (std::getenv("TEST_ENV") && std::string(std::getenv("TEST_ENV")) == "local")
	{
		auto buffer = wadReader.readFileData(getWadFilePath("DOOM_WAD_PATH"));
		wadReader.extractID(buffer, header, offset);
		ASSERT_EQ(std::string(header.WADType), "IWAD");
	}
	else
	{
		SUCCEED();
	}
}

TEST_F(WADReaderTests, HandleHeaderIDPWAD)
{
	if (std::getenv("TEST_ENV") && std::string(std::getenv("TEST_ENV")) == "local")
	{
		auto buffer = wadReader.readFileData(getWadFilePath("MYTESTMAP_WAD_PATH"));
		wadReader.extractID(buffer, header, offset);
		ASSERT_EQ(std::string(header.WADType), "PWAD");
	}
	else
	{
		SUCCEED();
	}
}

TEST_F(WADReaderTests, HandleTotalLumps)
{
	if (std::getenv("TEST_ENV") && std::string(std::getenv("TEST_ENV")) == "local")
	{
		auto buffer = wadReader.readFileData(getWadFilePath("DOOM_WAD_PATH"));
		offset += 4;
		wadReader.extractNumDirectories(buffer, header, offset);
		ASSERT_EQ(header.numDirectories, 2306);
	}
	else
	{
		SUCCEED();
	}
}

TEST_F(WADReaderTests, HandleRead2Bytes)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06}};

	// The bytes are stored in order in memory as 01 02 03 04 05 06
	// Because the elements of the array are single bytes, there is no endianness applied to the individual bytes
	// When interpreting the bytes in memory as two byte integers on a little endian machine, we will get:
	// 0x0201 from bytes 01 and 02
	// 0x0403 from bytes 03 and 04,
	// 0x0605 from bytes 05 and 06
	// For each pair of bytes, the byte at the lower address is the LSB, and the byte at the higher address is the MSB
	// - The byte 0x01 (lower address) is the LSB, and the byte 0x02 (higher address) is the MSB, forming the two-byte integer value 0x0201.
	// - The byte 0x03 (lower address) is the LSB, and the byte 0x04 (higher address) is the MSB, forming the two-byte integer value 0x0403.
	// - The byte 0x05 (lower address) is the LSB, and the byte 0x06 (higher address) is the MSB, forming the two-byte integer value 0x0605.
	ASSERT_EQ(wadReader.read2Bytes(buffer, 0), 0x0201);
	ASSERT_EQ(wadReader.read2Bytes(buffer, 2), 0x0403);
	ASSERT_EQ(wadReader.read2Bytes(buffer, 4), 0x0605);
}

TEST_F(WADReaderTests, HandleReadOutOfBounds2Bytes)
{
	std::vector<std::byte> buffer = {std::byte{0x01}};
	EXPECT_THROW(wadReader.read2Bytes(buffer, 0), std::runtime_error);
}

TEST_F(WADReaderTests, HandleOffsetOutOfBounds2Bytes)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06}};
	EXPECT_THROW(wadReader.read2Bytes(buffer, -1), std::runtime_error);
}

TEST_F(WADReaderTests, HandleOffsetOutOfBoundsGreater2Bytes)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}};
	EXPECT_THROW(wadReader.read2Bytes(buffer, 4), std::runtime_error);
}

TEST_F(WADReaderTests, HandleOutOfBoundsEqual2Bytes)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}};
	ASSERT_EQ(wadReader.read2Bytes(buffer, 0), 0x0201);
}

TEST_F(WADReaderTests, HandleRead4Bytes)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06}};

	// The bytes are stored in order in memory as 01 02 03 04 05 06
	// Because the elements of the array are single bytes, there is no endianness applied to the individual bytes
	// When interpreting the bytes in memory as four byte integers on a little endian machine, we will get:
	// 0x04030201 from bytes 04, 03, 01 and 02
	// For each pair of bytes, the byte at the lower address is the LSB, and the byte at the higher address is the MSB
	// - The byte 0x01 (lower address) is the LSB, and the byte 0x04 (higher address) is the MSB, forming the four-byte integer value 0x04030201.

	ASSERT_EQ(wadReader.read4Bytes(buffer, 0), 0x04030201);
}

TEST_F(WADReaderTests, HandleReadOutOfBounds)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}};
	EXPECT_THROW(wadReader.read4Bytes(buffer, 0), std::runtime_error);
}

TEST_F(WADReaderTests, HandleOffsetOutOfBounds)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06}};
	EXPECT_THROW(wadReader.read4Bytes(buffer, -1), std::runtime_error);
}

TEST_F(WADReaderTests, HandleOffsetOutOfBoundsGreater)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}, std::byte{0x05}, std::byte{0x06}};
	EXPECT_THROW(wadReader.read4Bytes(buffer, 7), std::runtime_error);
}

TEST_F(WADReaderTests, HandleOutOfBoundsEqual)
{
	std::vector<std::byte> buffer = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}};
	ASSERT_EQ(wadReader.read4Bytes(buffer, 0), 0x04030201);
}