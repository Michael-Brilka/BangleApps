#include "DecodeData.h"

bool DecodeData::determineLastBit(std::vector<char> byteSequence, int bitlength){
    uint8_t lastByte = 0;
    bool lastBit;
    int index = bitlength /8;
    int remainder = bitlength % 8;
    if(remainder == 0){
        lastByte = byteSequence[index -1];
        lastBit = (lastByte & 1) == 1;
        return lastBit;
    }
    lastByte = byteSequence[index];
    lastByte = lastByte >> 8-remainder;
    lastBit = (lastByte & 1) == 1;
    return lastBit;
}

uint8_t DecodeData::determineFillerByte(std::vector<char> byteSequence, int bitlength, bool* lastBitRET, int* index, uint8_t fillerStrategie){
    uint8_t lastByte = 0;
    *index = bitlength /8;
    int remainder = bitlength % 8;
    if(remainder == 0){
        lastByte = byteSequence[*index -1];
        *lastBitRET = (lastByte & 1) == 1;
        return lastByte;
    }
    lastByte = byteSequence[*index];
    lastByte = lastByte >> 8-remainder;
    bool lastBit = (lastByte & 1) == 1;
    *lastBitRET = lastBit;
    bool called = false;
    for (int i = 0; i < 8-remainder; i++)
    {
        lastByte = lastByte << 1;
        lastByte = lastByte | DecodeData::getFiller(fillerStrategie, lastBit, called);
        called = true;
    }
    *index = *index+1; 
    return lastByte;
    
}

bool DecodeData::getFiller(uint8_t fillerStrategie, bool last_bit, bool called){
    switch (fillerStrategie)
    {
    case 0:
        return 0;
        break;
    
    case 1:
        if (called)
        {
            return 0;
            break;
        }
        
        return 1;
        break;
    
    case 2:
        return 1;
        break;
    
    case 3:
        return last_bit;
        break;
    }
    return 0;
}

int DecodeData::decode12Bits(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie){
    bool bit = false;
    int decodedResult = 0;

    uint8_t entry = byteSequence[0];
    uint8_t sizeLeft = 12;

    if(12-reduction >7){
        char* p = (char*)&decodedResult;
        *(p) = entry;
        entry = byteSequence[1];
        sizeLeft = 4;
    }
    
    for (int i = 0; i < sizeLeft-reduction; i++)
    {
        decodedResult = decodedResult << 1;
        bit = entry & 128;
        decodedResult = decodedResult | bit;
        entry = entry << 1;
    }     

    bool called = false;
    bool fillerbit = false;

    for (int i = 0; i < reduction; i++)
    {
        fillerbit = getFiller(fillerStrategie, bit, called);
        decodedResult = decodedResult << 1;
        decodedResult = decodedResult | fillerbit;
        called = true;
    }   

    return decodedResult;
}

int DecodeData::decode15Bits(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie){
    bool bit = false;
    int decodedResult = 0;

    uint8_t entry = byteSequence[0];
    uint8_t sizeLeft = 15;

    if(reduction == 0){
        decodedResult = decodedResult | uint8_t(byteSequence[0]);
        decodedResult = decodedResult << 8;
        decodedResult = decodedResult | uint8_t(byteSequence[1]);
        decodedResult = decodedResult >> 1;
        return decodedResult;
    }

    if(15-reduction >7){
        char* p = (char*)&decodedResult;
        *(p) = entry;
        entry = byteSequence[1];
        sizeLeft = 7;
    }
    
    for (int i = 0; i < sizeLeft-reduction; i++)
    {
        decodedResult = decodedResult << 1;
        bit = entry & 128;
        decodedResult = decodedResult | bit;
        entry = entry << 1;
    }     

    bool called = false;
    bool fillerbit = false;

    for (int i = 0; i < reduction; i++)
    {
        fillerbit = getFiller(fillerStrategie, bit, called);
        decodedResult = decodedResult << 1;
        decodedResult = decodedResult | fillerbit;
        called = true;
    }   

    return decodedResult;
}

int DecodeData::decode16Bits(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie){
    bool bit = false;
    int decodedResult = 0;

    uint8_t entry = byteSequence[0];
    uint8_t sizeLeft = 16;

    if(reduction == 0){
        decodedResult = decodedResult | uint8_t(byteSequence[0]);
        decodedResult = decodedResult << 8;
        decodedResult = decodedResult | uint8_t(byteSequence[1]);
        return decodedResult;
    }

    if(16-reduction >7){
        char* p = (char*)&decodedResult;
        *(p) = entry;
        entry = byteSequence[1];
        sizeLeft = 8;
    }
    
    for (int i = 0; i < sizeLeft-reduction; i++)
    {
        decodedResult = decodedResult << 1;
        bit = entry & 128;
        decodedResult = decodedResult | bit;
        entry = entry << 1;
    }     

    bool called = false;
    bool fillerbit = false;

    for (int i = 0; i < reduction; i++)
    {
        fillerbit = getFiller(fillerStrategie, bit, called);
        decodedResult = decodedResult << 1;
        decodedResult = decodedResult | fillerbit;
        called = true;
    }   

    return decodedResult;
}

float DecodeData::decode32BitsF(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie, int* doubleMode, uint8_t decodeSetting){
    float result = 0;
    char* p  = (char*)&result;

    if(decodeSetting == 0){
        if(reduction == 0){
            for (int i = 0; i < 4; i++)
            {
                *(p +3-i) = byteSequence[i];
            }
            bool sign = ((byteSequence[0] & 128)>>7) ==1;
            uint8_t higher = byteSequence[0] &127;
            uint8_t lower = byteSequence[1];
            uint16_t exponent = higher;
            exponent = exponent << 8;
            exponent = exponent | lower;
            exponent = exponent >> 7;
            int expo = exponent;
            if(sign){
                expo = -expo;
            }
            doubleMode[1] = expo;
            return result;
        }
        
        int index = (32-reduction)/8;
        //copy
        for (int i = 0; i < index; i++)
        {
            *(p + (3-i)) = byteSequence[i];
        }

        bool lastBit;
        //First filler byte
        *(p+(3-index)) = DecodeData::determineFillerByte(byteSequence, (32-reduction), &lastBit, &index, fillerStrategie);

        bool filler = getFiller(fillerStrategie, lastBit, true);

        //set rest to 0 or 1
        for (int i = index; i < 4; i++)
        {
            if(filler == 0){
                *(p + (3-i)) = 0;
            }
            else
            {
                *(p + (3-i)) = 255;
            }
        }
        //set exponent in doubleMode
        
        uint8_t exponent = byteSequence[0];
        uint8_t eLB = byteSequence[1];
        bool exponentLastBit = (((eLB)&128)>>7) == 1;
        bool sign = ((exponent & 128)>>7) == 1;
        exponent = exponent << 1;
        exponent = exponent | exponentLastBit;
        int expo = exponent;
        if(sign){
            expo = -expo;
        }
        doubleMode[1] = expo;
    }
    else
    {
        //byteSequence only holds mantisse
        bool sign = doubleMode[1] <0;
        uint8_t exponent = doubleMode[1] &255;

        bool exponentLastBit = exponent &1;
        exponent = exponent >> 1;

        uint8_t write = sign;
        write = write << 7;
        write = write | exponent;

        *(p+3) = write;

        write = exponentLastBit;

        //copy man
        uint8_t firstSeven = byteSequence[0];
        firstSeven = firstSeven >> 1;
        write = write << 7;
        write = write | firstSeven;

        *(p+2) = write;

        bool written = false;
        int writeIndex = 0;
        int readIndex = 7;
        int byteSequenceIndex = 0;

        //copy auto
        for (int i = 0; i < 16-reduction; i++)
        {
            /* code */
            uint8_t read = byteSequence[byteSequenceIndex];
            read = read << readIndex;
            bool bitToWrite = read &128;

            readIndex++;
            if(readIndex == 8){
                readIndex = 0;
                byteSequenceIndex ++;
            }

            write = write << 1;
            write = write | bitToWrite;
            writeIndex ++;

            if(writeIndex == 8){
                writeIndex = 0;
                *(p+1-1*written) = write;
                written = true;
            }
        }
        
        //copy filler
        bool lastbit = DecodeData::determineLastBit(byteSequence, (32-1-8-reduction));
        bool filler = false;
        bool called = false;
        for (int i = 0; i < reduction; i++)
        {
            filler = getFiller(fillerStrategie, lastbit, called);
            called = true;

            write = write << 1;
            write = write | filler;
            writeIndex ++;

            if(writeIndex == 8){
                writeIndex = 0;
                *(p+1-1*written) = write;
                written = true;
            }
        }
    }
    
    return result;
}

double DecodeData::decode64BitsD(std::vector<char> byteSequence, uint8_t reduction, uint8_t fillerStrategie, int* doubleMode, uint8_t decodeSetting){

    double result = 0;
    char* p  = (char*)&result;

    if(decodeSetting == 0){
        if(reduction == 0){
            for (int i = 0; i <8; i++)
            {
                *(p +7-i) = byteSequence[i];
            }
            bool sign = ((byteSequence[0] & 128)>>7) ==1;
            uint8_t higher = byteSequence[0] &127;
            uint8_t lower = byteSequence[1];
            uint16_t exponent = higher;
            exponent = exponent << 8;
            exponent = exponent | lower;
            exponent = exponent >> 4;
            int expo = exponent;
            if(sign){
                expo = -expo;
            }
            doubleMode[1] = expo;
            return result;
        }

        int index = (64-reduction)/8;
        //copy
        for (int i = 0; i < index; i++)
        {
            *(p + (7-i)) = byteSequence[i];
        }

        bool lastBit;
        //First filler byte
        *(p+(7-index)) = DecodeData::determineFillerByte(byteSequence, (64-reduction), &lastBit, &index, fillerStrategie);

        bool filler = getFiller(fillerStrategie, lastBit, true);
        
        //set rest to 0 or 1
        for (int i = index; i < 8; i++)
        {
            if(filler == 0){
                *(p + (7-i)) = 0;
            }
            else
            {
                *(p + (7-i)) = 255;
            }
            
        }

        bool sign = (byteSequence[0] & 128) ==1;
        uint16_t exponent = byteSequence[0] &127;
        exponent = exponent << 8;
        exponent = exponent | byteSequence[1];
        exponent = exponent >> 4;
        int expo = exponent;
        if(sign){
            expo = -expo;
        }
        doubleMode[1] = expo;
    }
    else
    {
        bool sign = doubleMode[1] <0;
        uint16_t exponentVal = doubleMode[1] &2047;

        uint8_t exponentLast4Bits = exponentVal &15;
        uint8_t exponent = exponentVal >> 4;

        uint8_t write = sign;
        write = write << 7;
        write = write | exponent;

        *(p+7) = write;

        write = exponentLast4Bits;

        uint8_t firstFour = byteSequence[0];
        firstFour = firstFour >> 4;
        write = write << 4;
        write = write | firstFour;

        *(p+6) = write;

        int timesWritten = 0;
        int writeIndex = 0;
        int readIndex = 7;
        int byteSequenceIndex = 0;

        for (int i = 0; i < 48-reduction; i++)
        {
            /* code */
            uint8_t read = byteSequence[byteSequenceIndex];
            read = read << readIndex;
            bool bitToWrite = read &128;

            readIndex++;
            if(readIndex == 8){
                readIndex = 0;
                byteSequenceIndex ++;
            }

            write = write << 1;
            write = write | bitToWrite;
            writeIndex ++;

            if(writeIndex == 8){
                writeIndex = 0;
                *(p+5-1*timesWritten) = write;
                timesWritten++;
            }
        }

        bool lastbit = DecodeData::determineLastBit(byteSequence, (52-reduction));
        bool filler = false;
        bool called = false;
        for (int i = 0; i < reduction; i++)
        {
            filler = getFiller(fillerStrategie, lastbit, called);
            called = true;

            write = write << 1;
            write = write | filler;
            writeIndex ++;

            if(writeIndex == 8){
                writeIndex = 0;
                *(p+5-1*timesWritten) = write;
                timesWritten++;
            }
        }

    }
    
    return result;
}

