#include <vector>
#include <cstdint>

class DecodeData
{
private:
    

public:
    bool determineLastBit(std::vector<char> byteSequence, int bitlength);
	uint8_t determineFillerByte(std::vector<char> byteSequence, int bitlength, bool* lastBitRET, int* index, uint8_t fillerStrategie);
	bool getFiller(uint8_t fillerStrategie,bool last_bit, bool called);
	int decode12Bits(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie);
	int decode15Bits(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie);
	int decode16Bits(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie);
	float decode32BitsF(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie, int* doubleMode, uint8_t decodeSetting);
	double decode64BitsD(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie, int* doubleMode, uint8_t decodeSetting);
};

