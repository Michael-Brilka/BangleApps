#pragma once
#include <vector>
#include <math.h>

#include "DataElements.h"

#include <ctime>
#include <time.h>

#include "ReadFromData.h"
#include "bangleJSMath.h"

#include <filesystem>
#include <iostream>
#include <fstream>

#include "../pugixml/src/pugixml.hpp"

class DecodeGlobal
{
public:

	DecodeGlobal(unsigned char* inputData, int _filelength, std::string _localPathString);

	void decode();
	void writeToDisk();


private:
	ReadFromData reader;
	int index = 1;
	int byteIndex = 0;
	bool byteStuffing = false;
	_int64 lastTimestamp = 0;
	int filelength = 0;
	bool endOfFile = false;
	std::string localPathString;


	std::string supervisor;
	std::string subject;
	bool saveXML = true;
	bool jsMath = true;
	bool writeAltitude = false;
	bool filenameSupervisor = true;
	bool filenameSubject = true;
	bool filenameDate = true;
	int numberSensors = 0;
	time_t timeDec;

	int idLength = 0;
	struct idMap
	{
		int localID = 0;
		int globalID = 0;
	};
	std::vector<idMap> idMapping;


	void decodeHeader();
	void decodeEntry();
	int decodeTime();

	void decodeHRM();
	void decodeBarometer();
	void decodeAccelerometer();
	void decodeMagnetude();
	void decodeCompass();
	void decodeGPS();

	void xmlHRM(DataElements::HRM hrm, pugi::xml_node head);
	void xmlBarometer(DataElements::Barometer barometer, pugi::xml_node head);
	void xmlAccelerometer(DataElements::Accelerometer accelerometer, pugi::xml_node head);
	void xmlMagnetude(DataElements::Magnetude magnetude, pugi::xml_node head);
	void xmlCompass(DataElements::Compass compass, pugi::xml_node head);
	void xmlGPS(DataElements::GPS gps, pugi::xml_node head);

	std::vector<DataElements::HRM> hrmEntrys;
	std::vector<DataElements::Barometer> barometerEntrys;
	std::vector<DataElements::Accelerometer> accelerometerEntrys;
	std::vector<DataElements::Magnetude> magnetudeEntrys;
	std::vector<DataElements::Compass> compassEntrys;
	std::vector<DataElements::GPS> gpsEntrys;

};

