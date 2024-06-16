#include <iostream>
#include <fstream>
#include <string> 
#include "Decoder.h"
#include <vector>
#include <filesystem>
#include <ctime>
#include "../pugixml/src/pugixml.hpp"
#include <conio.h>

using namespace std;


namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
    std::cout << argv[0] << std::endl;
    if (argc < 2) {
        std::cout << "ERROR: Wrong amount of arguments!" << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        _getch();
        exit(0);
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        ifstream myFile;
        myFile.open(argv[i], ios::in | ios::binary);


        myFile.seekg(0, myFile.end);
        int filelength = myFile.tellg();
        myFile.seekg(0, myFile.beg);

        char* buffer = new char[filelength];

        myFile.read(buffer, filelength);

        unsigned char* bufferDec = reinterpret_cast<unsigned char*>(buffer);

        DecodeGlobal decoder = DecodeGlobal(bufferDec, filelength, argv[0]);

        decoder.decode();

        decoder.writeToDisk();

        std::cout << "Press any key to exit..." << std::endl;
        _getch();
    }    

    std::cout << "Press any key to exit..." << std::endl;
    _getch();

    exit(0);
}