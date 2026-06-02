#pragma once
#include <vector>
#include <math.h>
#include <ctime>
#include <time.h>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "DataElements.h"
#include "ReadFromData.h"
#include "BangleJSMath.h"
#include "DecodeData.h"


class DecodeGlobal
{
public:

	DecodeGlobal(unsigned char* inputData, int _filelength, std::string _localPathString);

	void decode();
	void writeToDisk();
	int doubleModeALL = 0;
	int doubleSame = 0;
	int doublepm1 = 0;
	int headingevents = 0;


private:
	DecodeData decodeData;
	ReadFromData reader;
	int index = 1;
	int byteIndex = 0;
	bool byteStuffing = false;
	int64_t lastTimestamp = 0;
	int filelength = 0;
	bool endOfFile = false;
	std::string localPathString;

	uint8_t hrm_Reduction = 0;
	uint8_t hrm_filler = 0;

	uint8_t barometerMode = 0;
	bool temperature_Float32 = false;
	uint8_t temperature_Reduction = 0;
	uint8_t temperature_filler = 0;
	int barometerTemperatureDoubleMode[2];
	bool pressure_Float32 = false;
	uint8_t pressure_Reduction = 0;
	uint8_t pressure_filler = 0;
	int barometerPressureDoubleMode[2];
	bool heigth_Float32 = false;
	uint8_t height_Reduction = 0;
	uint8_t height_filler = 0;
	int barometerHeightDoubleMode[2];

	uint8_t accelerometerXYZ_Reduction = 0;
	uint8_t accelerometerXYZ_filler = 0;
	uint8_t magnitude_Reduction = 0;
	uint8_t magnitede_filler = 0;

	uint8_t accelrange = -1;
	double accelrangeSet = -1.0;
	
	uint8_t compassXYZ_Reduction = 0;
	uint8_t compassXYZ_filler = 0;
	bool compassHeading_Float32 = false;
	uint8_t compassHeading_Reduction = 0;
	uint8_t compassHeading_filler = 0;
	int compassHeadingDoubleMode[2];

	bool gpsLL_Float32 = false;
	uint8_t gpsLL_Reduction = 0;
	uint8_t gpsLL_filler = 0;
	int gpsLADoubleMode[2];
	int gpsLODoubleMode[2];
	bool gpsA_Float32 = false;
	uint8_t gpsA_Reduction = 0;
	uint8_t gpsA_filler = 0;
	int gpsADoubleMode[2];
	
	std::string supervisor;
	std::string subject;
	int version = 0;
	bool debug = false;
	bool jsMath = true;
	bool writeAltitude = false;
	bool filenameSupervisor = true;
	bool filenameSubject = true;
	bool filenameDate = true;
	bool folderSupervisor = true;
	bool folderSubject = true;
	bool folderDate = true;
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
	void decodeSize(uint8_t globalID);
	void decodeEntry();

	int64_t decodeTime();

	void decodeHRM();
	void decodeBarometer();
	void barometerTemperature(double* tempD, float* tempF);
	void barometerPressure(double* pressureD, double* altitudeD, float* pressureF, float* altitudeF);

	void decodeAccelerometer();
	void decodeMagnitude();
	void decodeCompass();
	void decodeGPS();
	void decodeMarker();

	std::vector<DataElements::GloveData> gloveEntrys;
	std::vector<DataElements::HRM> hrmEntrys;
	std::vector<DataElements::Barometer> barometerEntrys;
	std::vector<DataElements::Accelerometer> accelerometerEntrys;
	std::vector<DataElements::Magnitude> magnitudeEntrys;
	std::vector<DataElements::Compass> compassEntrys;
	std::vector<DataElements::GPS> gpsEntrys;
	std::vector<int64_t> markerEntrys;

};

