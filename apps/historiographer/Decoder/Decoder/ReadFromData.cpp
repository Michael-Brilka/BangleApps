#include "ReadFromData.h"

using namespace std;

ReadFromData::ReadFromData()
{
}

ReadFromData::ReadFromData(int _fileleangth, bool* _endOfFile, unsigned char* inputData)
{
    filelength = _fileleangth;
    endOfFile = endOfFile;
    data = inputData;
    currentByte = inputData[0];
}

char ReadFromData::readByteMax(int bitsToRead) {
    char output = 0;
    bool bit = 0;
    for (int i = 0; i < bitsToRead; i++) {
        bit = (currentByte & 128) == 128;
        output = output << 1;
        output = output | bit;
        currentByte = currentByte << 1;
        byteIndex++;
        if (!(byteIndex < 8)) {
            if (index < filelength) {
                currentByte = data[index];

                //check if byte is equal to 255 if yes mark end of file
                if (currentByte == 255) {
                    *endOfFile = true;
                }

                if (currentByte == 254) {
                    unsigned char nextByte = data[index + 1];
                    bit = (nextByte & 128) == 128;
                    currentByte = currentByte | bit;


                    if (byteStuffing == false) {
                        byteIndex = 0;
                    }
                    else
                    {
                        byteIndex = 1;
                        currentByte = currentByte << 1;
                        byteStuffing = false;
                    }

                    byteStuffing = true;
                }
                else {

                    if (byteStuffing == false) {
                        byteIndex = 0;
                    }
                    else
                    {
                        byteIndex = 1;
                        currentByte = currentByte << 1;
                        byteStuffing = false;
                    }
                }
                index++;
            }
            else
            {
                currentByte = 0;
                *endOfFile = true;
            }
        }
    }

    return output;
}

std::vector<char> ReadFromData::readBits(int bitsToRead) {
    // calculate how many bytes we read
    // + what remainder needs to be appendend
    int bytes = bitsToRead / 8;
    int remainder = bitsToRead % 8;

    vector<char> result = vector<char>();

    //all bytes 
    for (int i = 0; i < bytes; i++) {
        result.push_back(readByteMax(8));
    }

    // remainder
    int shifts = 8 - remainder;
    if (remainder != 0) {
        //get data
        char restData = readByteMax(remainder);
        //shift to left
        restData = restData << shifts;
        //everything is aligned to left

        result.push_back(restData);
    }

    return result;
}