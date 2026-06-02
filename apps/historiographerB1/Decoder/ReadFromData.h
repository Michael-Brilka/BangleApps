#pragma once
#include <vector>
class ReadFromData
{
public:
	ReadFromData();
	ReadFromData(int _fileleangth, bool* _endOfFile, unsigned char* inputData);

	char readByteMax(int bitsToRead);

	std::vector<char> readBits(int bitsToRead);

private:

	unsigned char currentByte = 0;
	int index = 1;
	int byteIndex = 0;
	bool byteStuffing = false;

	int filelength = 0;
	bool* endOfFile;

	unsigned char* data;

};

