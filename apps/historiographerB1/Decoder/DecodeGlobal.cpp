#include "DecodeGlobal.h"

using namespace std;

namespace fs = std::filesystem;

DecodeGlobal::DecodeGlobal(unsigned char* inputData, int _filelength, string _localPathString)
{
    filelength = _filelength;
    reader = ReadFromData(filelength, &endOfFile, inputData);
    localPathString = _localPathString;
}

void DecodeGlobal::decode()
{
    decodeHeader();
    while (index < filelength && !endOfFile)
    {
        decodeEntry();
    }
}

void DecodeGlobal::decodeHeader() {
    version = reader.readByteMax(8);
    unsigned char lengthArtztname = reader.readByteMax(8);
    bool bit = false;
    supervisor = "";
    if (lengthArtztname == 0) {
        supervisor = "Unknown";
    }

    vector<char> arztnameVector = reader.readBits(lengthArtztname * 8);

    for (int i = 0; i < arztnameVector.size(); i++) {
        string asString;
        asString = arztnameVector[i];
        supervisor.append(asString);
    }


    unsigned char lengthPatientenName = reader.readByteMax(8);

    subject = "";

    if (lengthPatientenName == 0) {
        subject = "Unknown";
    }

    vector<char> patientennameVector = reader.readBits(lengthPatientenName * 8);

    for (int i = 0; i < lengthPatientenName; i++) {
        string asString;
        asString = patientennameVector[i];
        subject.append(asString);
    }

    debug = reader.readByteMax(1) == 1;

    idLength = reader.readByteMax(8);
    bool getIDs = true;

    unsigned char localID = 0;
    unsigned char globalID = 0;

    unsigned char maxID = 0;

    for (int i = 0; i < idLength; i++)
    {
        maxID = maxID << 1;
        maxID = maxID | 1;
    }

    while (getIDs)
    {
        localID = reader.readByteMax(idLength);
        if (localID != maxID) {
            globalID = reader.readByteMax(8);
            idMap map = { localID, globalID };

            idMapping.push_back(map);
            if(globalID == 3){
                accelrange = reader.readByteMax(2);

                accelrangeSet = 4096.0 *(4 >> accelrange);
            }
            if(globalID == 5){
                compassHeading_Float32 = reader.readByteMax(1);
            }
            if(globalID == 6){
                gpsA_Float32 = reader.readByteMax(1);
                gpsLL_Float32 = gpsA_Float32;
            }
            if(version == 0)
            	decodeSize(globalID);
        }
        else
        {
            //End of IDs
            getIDs = false;
            idMap map = { localID,0 };

            idMapping.push_back(map);
        }

    }

    std::cout << "Version: " << version << "\n";
    std::cout << "Supervisor: " << supervisor << "\n";
    std::cout << "Subject: " << subject << "\n";
    std::cout << "Sensors: " << int(idMapping.size() - 1) << "\n";

    if(debug){
        bool fastUpdate = reader.readByteMax(1) == 1;
        for (int i = 0; i < idMapping.size(); i++)
        {
            idMap map = idMapping[i];
            switch (map.globalID)
            {
                case 1: //HRM
                {
                    int selectedHRM = reader.readByteMax(3)-1;
                    std::string const hrmSpeeds[6] = {"100","50","25","12.5","6.25","5"};
                    std::cout << "Recording HRM at: "<< hrmSpeeds[selectedHRM]<<"Hz\n";
                    break;
                }                
                case 3://accel
                case 4://magnitude
                {
                    bool accelBypass = reader.readByteMax(1) == 1;
                    string accelfilter = (reader.readByteMax(1) == 1)?"2":"9";
                    int accelOutputDatarate = reader.readByteMax(4);
                    int accelSamples = reader.readByteMax(3); 
                    bool accelResMode = reader.readByteMax(1) == 1;

                    string accelOutputDataRateText[12] = {"12.5Hz","25Hz","50Hz","100Hz","200Hz","400Hz","800Hz","1600Hz","0.781Hz","1.563Hz","3.125Hz","6.25Hz"};
                    std::cout << "Bypassing filter: "<< accelBypass<<", using filter: ODR/"<< accelfilter<< ", Samples used for averageing: "<<accelSamples<<", RES mode: "<< accelResMode<<"\n";
                    std::cout << "Recording Accelerometer Sensor at: "<< accelOutputDataRateText[accelOutputDatarate]<<"\n";
                    break;
                }
                case 5: //compass
                {
                    std::vector<char> compassSkips = reader.readBits(16);
                    int compassSkipsDecoded = decodeData.decode16Bits(compassSkips, 0,0);
                    int compassIntervall = 20*compassSkipsDecoded;
                    
                    if(compassSkipsDecoded < 50){
                        std::cout << "Recording Compass every: "<< compassIntervall<<" ms\n";    
                    }
                    if(compassSkipsDecoded < 3000){
                        std::cout << "Recording Compass every: "<< compassIntervall/1000<<" s\n";    
                    }
                    else
                    {
                        std::cout << "Recording Compass every: "<< compassIntervall/1000/60<<" min\n";   
                    }
                    break;
                }
                case 6: //GPS
                {
                    std::vector<char> gpsSkips = reader.readBits(16);
                    int gpsskipsDecoded = decodeData.decode16Bits(gpsSkips, 0,0);
                    
                    bool energysaveGPS = reader.readByteMax(1) == 1;

                    std::cout << "Recording GPS in energy saving mode: "<<energysaveGPS<<"\n";

                    if(gpsskipsDecoded < 60){
                        std::cout << "Recording GPS every: "<< gpsskipsDecoded<<" s\n";    
                    }
                    if(gpsskipsDecoded < 3600){
                        std::cout << "Recording GPS every: "<< gpsskipsDecoded/60<<" min\n";    
                    }
                    else
                    {
                        std::cout << "Recording GPS every: "<< gpsskipsDecoded/60/60<<" hours\n";   
                    }

                    break;
                }
            }
        }

        //ramsize
        std::vector<char> ramsize = reader.readBits(16);
        int ramsizeDecoded = decodeData.decode16Bits(ramsize, 0,0);
        std::cout << "Ramsize: "<<ramsizeDecoded<< "\n";

        //clock settings
        bool showWidgets = reader.readByteMax(1) == 1;
        bool showClock = reader.readByteMax(1) == 1;
        bool showDate = reader.readByteMax(1) == 1;
        bool updateDate = reader.readByteMax(1) == 1;
        std::cout << "Showing Widgets: "<< showWidgets<<", showing clock:"<< showClock<<", showing date:"<< showDate <<", update date:"<<updateDate<< "\n";
    }

    filenameSupervisor = reader.readByteMax(1) & 1;
    filenameSubject = reader.readByteMax(1) & 1;
    filenameDate = reader.readByteMax(1) & 1;
    folderSupervisor = reader.readByteMax(1) & 1;
    folderSubject = reader.readByteMax(1) & 1;
    folderDate = reader.readByteMax(1) & 1;

    unsigned char yearLength = reader.readByteMax(8);

    vector<char> yearV = reader.readBits(yearLength);
    int yearReal = 0;

    int yearBitsRemainder = yearLength % 8;
    unsigned char lastEntry = yearV[yearV.size() - 1];
    unsigned char fitstEntry = yearV[0];

    for (int i = 0; i < 8 - yearBitsRemainder; i++) {
        lastEntry = lastEntry >> 1;
    }


    for (int i = 0; i < yearBitsRemainder; i++)
    {
        bit = lastEntry & 1;
        yearReal = yearReal | bit;
        yearReal = yearReal << 1;
        lastEntry = lastEntry >> 1;
    }

    int size = yearV.size();

    for (int j = size - 2; j > -1; j--) {
        lastEntry = yearV[j];
        for (int i = 0; i < 7; i++)
        {
            bit = lastEntry & 1;
            yearReal = yearReal | bit;
            yearReal = yearReal << 1;
            lastEntry = lastEntry >> 1;
        }
        bit = lastEntry & 1;
        yearReal = yearReal | bit;
    }


    unsigned char month = reader.readByteMax(4);
    unsigned char day = reader.readByteMax(5) + 1;
    unsigned char hours = reader.readByteMax(5);
    unsigned char minutes = reader.readByteMax(6);

    numberSensors = int(idMapping.size() - 1);

    struct tm timeinfo = { 0 };
    timeinfo.tm_year = (yearReal - 1900);
    timeinfo.tm_mon = month;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hours;
    timeinfo.tm_min = minutes;
    timeinfo.tm_isdst = -1;
    timeDec = mktime(&timeinfo);

    lastTimestamp = timeDec;
    lastTimestamp = lastTimestamp *1000;

   
    std::cout << "Date: " << int(day) << "." << int(month) + 1 << "." << int(yearReal) << " at: " << int(hours) << ":" << int(minutes) << "\n";
}

void DecodeGlobal::decodeSize(uint8_t globalID){
    switch (globalID)
    {
    case 1://HRM
        hrm_Reduction = reader.readByteMax(4);
        hrm_filler = reader.readByteMax(2);
        break;
    case 2://Barometer
        barometerMode = reader.readByteMax(2);
        barometerTemperatureDoubleMode[0] = reader.readByteMax(2);
        barometerTemperatureDoubleMode[1] = -900000;
        temperature_Float32 = reader.readByteMax(1) == 1;
        temperature_Reduction = reader.readByteMax(4);
        temperature_filler = reader.readByteMax(2);
        barometerPressureDoubleMode[0] = reader.readByteMax(2);
        barometerPressureDoubleMode[1] = -900000;
        pressure_Float32 = reader.readByteMax(1) == 1;
        pressure_Reduction = reader.readByteMax(4);
        pressure_filler = reader.readByteMax(2);
        jsMath = reader.readByteMax(1) == 1;
        writeAltitude = reader.readByteMax(1) == 1;
        if(writeAltitude){
            barometerHeightDoubleMode[0] = reader.readByteMax(2);
            barometerHeightDoubleMode[1] = -900000;
            heigth_Float32 = reader.readByteMax(1) == 1;
            height_Reduction = reader.readByteMax(4);
            height_filler = reader.readByteMax(2);        
        }
        break;
    case 3://Accelerometer
        accelerometerXYZ_Reduction = reader.readByteMax(4);
        accelerometerXYZ_filler = reader.readByteMax(2);
        accelrange = reader.readByteMax(2);
        accelrangeSet = 4096.0 *(4 >> accelrange);
        break;
    case 4://Magnitude
        magnitude_Reduction = reader.readByteMax(4);
        magnitede_filler = reader.readByteMax(2);
        if(accelrange == -1){
            accelrange = reader.readByteMax(2);
            accelrangeSet = 4096.0 *(4 >> accelrange);
        }
        break;
    case 5://Compass
        compassXYZ_Reduction = reader.readByteMax(4);
        compassXYZ_filler = reader.readByteMax(2);
        compassHeadingDoubleMode[0] = reader.readByteMax(2);
        std::cout << std::to_string(compassHeadingDoubleMode[0]) << " mode\n";
        compassHeadingDoubleMode[1] = -900000;
        compassHeading_Float32 = reader.readByteMax(1) == 1;
        compassHeading_Reduction = reader.readByteMax(4);
        compassHeading_filler = reader.readByteMax(2);
        break;
    case 6://GPS
        gpsLADoubleMode[0] = reader.readByteMax(2);
        gpsLADoubleMode[1] = -900000;
        gpsLODoubleMode[0] = gpsLADoubleMode[0];
        gpsLODoubleMode[1] = -900000;
        gpsLL_Float32 = reader.readByteMax(1) == 1;
        gpsLL_Reduction = reader.readByteMax(4);
        gpsLL_filler = reader.readByteMax(2);
        gpsADoubleMode[0] = reader.readByteMax(2);
        gpsADoubleMode[1] = -900000;
        gpsA_Float32 = reader.readByteMax(1) == 1;
        gpsA_Reduction = reader.readByteMax(4);
        gpsA_filler = reader.readByteMax(2);
        break;

    case 7: 
        std::cout << "Using Markers\n";
        break;

    case 8:
        std::cout << "Using Glove Data\n";
        break;
    
    default:
        std::cout<<"Error while decoding the bitsize, no ID case for ID "<<std::to_string(globalID)<<" found!";
        exit(0);
        break;
    }
}

void DecodeGlobal::decodeEntry() {
    unsigned char localid = reader.readByteMax(idLength);

    int globalID = -1;

    for (int i = 0; i < idMapping.size(); i++)
    {
        idMap map = idMapping[i];
        if (map.localID == localid) {
            globalID = map.globalID;
            break;
        }
    }

    switch (globalID)
    {

    case 1:
        //HRM
        decodeHRM();
        break;
    case 2:
        //Barometer
        decodeBarometer();
        break;
    case 3:
        //Accelerometer
        decodeAccelerometer();
        break;
    case 4:
        //Magnitude
        decodeMagnitude();
        break;
    case 5:
        //Compass
        decodeCompass();
        break;
    case 6:
        //GPS
        decodeGPS();
        break;
    case 7:
        //Marker
        decodeMarker();
        break;

    case 0:
        std::cout << "End1: " << localid<<endl;
        index = filelength;
        break;
    default:
        // end of file
        std::cout << "End2: " << globalID << endl;
        break;
    }
}

int64_t DecodeGlobal::decodeTime() {
    uint8_t longDeltatime = reader.readByteMax(1);
    int time = 0;
    if (longDeltatime == 0) {
        time = uint8_t(reader.readByteMax(8));
    }
    else {
        std::vector<char> timeAsChar = reader.readBits(32);

        for (int i = 0; i < 4; i++)
        {
            time = time << 8;
            time = time | uint8_t(timeAsChar[i]);
        }
    }
    lastTimestamp = lastTimestamp + time;
    return lastTimestamp;
}

void DecodeGlobal::decodeHRM() {
    int64_t time = DecodeGlobal::decodeTime();

    int ppgD;

    if(version == 0){
        std::vector<char> ppg = reader.readBits(12-hrm_Reduction);
        ppgD = decodeData.decode12Bits(ppg, hrm_Reduction, hrm_filler);
    }
    else{
        bool positiv = reader.readByteMax(1);
        int ppg = reader.readByteMax(7);
        
        if (positiv == false) {
            ppg = -ppg;
            ppg -= 1;
        }
        
        ppgD = ppg;
    }
    if (!endOfFile) {
        DataElements::HRM hrm = { time, ppgD };
        hrmEntrys.push_back(hrm);
    }
}

void DecodeGlobal::decodeBarometer() {
    int64_t time = DecodeGlobal::decodeTime();
    DataElements::Barometer barometer; 
    double tempD = 0, pressD = 0, altitudeD = 0;
    float tempF = 0, pressF = 0, altitudeF = 0;
    switch (barometerMode)
    {
        case 0://Both
        {
            barometerTemperature(&tempD, &tempF);
            barometerPressure(&pressD, &altitudeD, &pressF, &altitudeF); 
            break;
        }
        case 1://Temperature
        {
            barometerTemperature(&tempD, &tempF);
            break;
        }
        case 2://Pressure
        {            
            barometerPressure(&pressD, &altitudeD, &pressF, &altitudeF);
            break;
        }
        case 3://Seperate
        {
            uint8_t mode = reader.readByteMax(2);
            switch (mode)
            {
            case 1:{
                barometerTemperature(&tempD, &tempF);
                break;
            }
            case 2:{
                barometerPressure(&pressD, &altitudeD, &pressF, &altitudeF);
                break;
            }
            case 3:{
                barometerTemperature(&tempD, &tempF);
                barometerPressure(&pressD, &altitudeD, &pressF, &altitudeF);
                break;
            }
            }   
        }
    }
    

    if (!endOfFile) {
        barometer = { time, tempD,pressD,altitudeD, tempF, pressF, altitudeF};    
        barometerEntrys.push_back(barometer);
    }
}

void DecodeGlobal::barometerTemperature(double* tempD, float* tempF){
    
    uint8_t decodeSetting = 0;
    if(version == 0)
        decodeSetting = reader.readByteMax(barometerTemperatureDoubleMode[0]);

    int toRead = temperature_Float32?32-temperature_Reduction:64-temperature_Reduction;

    if(decodeSetting>0){
        toRead = toRead - 1 -8 -3*!temperature_Float32;
        if (barometerTemperatureDoubleMode[0] == 2)
        {
            switch (decodeSetting)
            {
            case 1:{
                barometerTemperatureDoubleMode[1]--; 
                break;
            }
            case 2:{
                barometerTemperatureDoubleMode[1]++;
                break;
            }
            }
        }
        
    }
    std::vector<char> temp = reader.readBits(toRead);

    if(temperature_Float32){
        *tempF = decodeData.decode32BitsF(temp, temperature_Reduction, temperature_filler, barometerTemperatureDoubleMode, decodeSetting);
    }
    else{
        *tempD = decodeData.decode64BitsD(temp, temperature_Reduction, temperature_filler, barometerTemperatureDoubleMode, decodeSetting);
    }
}

void DecodeGlobal::barometerPressure(double* pressureD, double* altitudeD, float* pressureF, float* altitudeF){
    
    uint8_t decodeSetting = 0;
    if(version == 0)
        decodeSetting = reader.readByteMax(barometerPressureDoubleMode[0]);

    int toRead = pressure_Float32?32-pressure_Reduction:64-pressure_Reduction;

    if(decodeSetting>0){
        toRead = toRead - 1 -8 -3*!pressure_Float32;
        if (barometerPressureDoubleMode[0] == 2)
        {
            switch (decodeSetting)
            {
            case 1:{
                barometerPressureDoubleMode[1]--; 
                break;
            }
            case 2:{
                barometerPressureDoubleMode[1]++;
                break;
            }
            }
        }
        
    }
    std::vector<char> press = reader.readBits(toRead);

    if(pressure_Float32){
        *pressureF = decodeData.decode32BitsF(press, pressure_Reduction, pressure_filler, barometerPressureDoubleMode, decodeSetting);
    }
    else{
        *pressureD = decodeData.decode64BitsD(press, pressure_Reduction, pressure_filler, barometerPressureDoubleMode, decodeSetting);
    }

    if (writeAltitude) {
        
        decodeSetting = 0;
        if(version == 0)
            decodeSetting = reader.readByteMax(barometerHeightDoubleMode[0]);

        toRead = heigth_Float32?32-height_Reduction:64-height_Reduction;

        if(barometerHeightDoubleMode[0]>0){
            toRead = toRead - 1 -8 -3*!heigth_Float32;
            if (barometerHeightDoubleMode[0] == 2)
            {
                switch (decodeSetting)
                {
                case 1:{
                    barometerHeightDoubleMode[1]--; 
                    break;
                }
                case 2:{
                    barometerHeightDoubleMode[1]++;
                    break;
                }
                }
            }
            
        }
        std::vector<char> altitude = reader.readBits(toRead);

        if(heigth_Float32){
            *altitudeF = decodeData.decode32BitsF(altitude, height_Reduction, height_filler, barometerHeightDoubleMode, decodeSetting);
        }
        else{
            *altitudeD = decodeData.decode64BitsD(altitude, height_Reduction, height_filler, barometerHeightDoubleMode, decodeSetting);
        }

    }
    else {
        
        if (jsMath) {
            
            double multiplicantBangle = (1.0 - BangleJsMath::jswrap_math_pow((pressure_Float32?*pressureF:*pressureD / 1013.25), 0.1903));
            *altitudeD = 44330 * multiplicantBangle;
        }
        else
        {
            float *t = pressureF;
            float t2 = *pressureF;
            double pow1 = ((pressure_Float32?*pressureF:*pressureD) / 1013.25);
            double powRes = pow(pow1, (1 / 5.255));
            double multiplicant = (1 - powRes);
            double res = 44330 * multiplicant;
            *altitudeD = res;
            res = 0;
            res = 1;
        }
    }
}

void DecodeGlobal::decodeAccelerometer() {
    int64_t time = DecodeGlobal::decodeTime();

    // get data from Array

    bool positiv = reader.readByteMax(1);

    std::vector<char> xAccel = reader.readBits(15-accelerometerXYZ_Reduction);

    int xAccelD = decodeData.decode15Bits(xAccel, accelerometerXYZ_Reduction, accelerometerXYZ_filler);
    if (positiv == false) {
        xAccelD = -xAccelD;
        xAccelD -=1;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> yAccel = reader.readBits(15-accelerometerXYZ_Reduction);

    int yAccelD = decodeData.decode15Bits(yAccel, accelerometerXYZ_Reduction, accelerometerXYZ_filler);
    if (positiv == false) {
        yAccelD = -yAccelD;
        yAccelD -=1;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> zAccel = reader.readBits(15-accelerometerXYZ_Reduction);

    int zAccelD = decodeData.decode15Bits(zAccel, accelerometerXYZ_Reduction, accelerometerXYZ_filler);
    if (positiv == false) {
        zAccelD = -zAccelD;
        zAccelD -=1;
    }

    //convert Data back to double
    double xAccelerometerData = xAccelD / accelrangeSet;
    double yAccelerometerData = yAccelD / accelrangeSet;
    double zAccelerometerData = zAccelD / accelrangeSet;



    if (!endOfFile) {
        DataElements::Accelerometer accel = { time, xAccelerometerData , yAccelerometerData , zAccelerometerData };
        accelerometerEntrys.push_back(accel);
    }
}

void DecodeGlobal::decodeMagnitude() {
    int64_t time = DecodeGlobal::decodeTime();

    std::vector<char> magnitude = reader.readBits(16-magnitude_Reduction);

    int magnitudeD = decodeData.decode16Bits(magnitude, magnitude_Reduction, magnitede_filler);

    //convert Data back to double
    double magnitudeData = magnitudeD / accelrangeSet;

    if (!endOfFile) {
        DataElements::Magnitude mag = { time, magnitudeData };
        magnitudeEntrys.push_back(mag);
    }

}

void DecodeGlobal::decodeCompass() {
    int64_t time = DecodeGlobal::decodeTime();

    bool positiv = reader.readByteMax(1);

    std::vector<char> xCompass = reader.readBits(12-compassXYZ_Reduction);
    int xCompassD = decodeData.decode12Bits(xCompass, compassXYZ_Reduction, compassXYZ_filler);
    if (positiv == false) {
        xCompassD = -xCompassD;
        xCompassD -=1;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> yCompass = reader.readBits(12-compassXYZ_Reduction);
    int yCompassD = decodeData.decode12Bits(yCompass, compassXYZ_Reduction, compassXYZ_filler);
    if (positiv == false) {
        yCompassD = -yCompassD;
        yCompassD -=1;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> zCompass = reader.readBits(12-compassXYZ_Reduction);
    int zCompassD = decodeData.decode12Bits(zCompass, compassXYZ_Reduction, compassXYZ_filler);
    if (positiv == false) {
        zCompassD = -zCompassD;
        zCompassD -=1;
    }

    uint8_t decodeSetting = 0;
    if(version == 0)
        decodeSetting = reader.readByteMax(compassHeadingDoubleMode[0]);

    int toRead = compassHeading_Float32?32-compassHeading_Reduction:64-compassHeading_Reduction;
    int doubleModeAllPrev = doubleModeALL;

    headingevents++;
    if(decodeSetting>0){
        toRead = toRead - 1 -8 -3*!compassHeading_Float32;
        doubleModeALL++;
        if (compassHeadingDoubleMode[0] == 2)
        {
            switch (decodeSetting)
            {
            case 1:{
                compassHeadingDoubleMode[1]--;
                doublepm1++; 
                break;
            }
            case 2:{
                compassHeadingDoubleMode[1]++;
                doublepm1++;
                break;
            }
            default:doubleSame++;
            }
        }
        else
        {
            doubleSame++;
        }   
    }
    

    std::vector<char> heading = reader.readBits(toRead);

    

    double headingD = 0;
    float headingF = 0;

    if(compassHeading_Float32){
        headingF = decodeData.decode32BitsF(heading, compassHeading_Reduction, compassHeading_filler, compassHeadingDoubleMode, decodeSetting);
        if(headingF > 800.0){
            std::cout<<"E";
        }
    }
    else{
        headingD = decodeData.decode64BitsD(heading, compassHeading_Reduction, compassHeading_filler, compassHeadingDoubleMode, decodeSetting);
        if(headingD > 800.0){
            std::cout<<"E";
        }
    }
    
    if (!endOfFile) {
        DataElements::Compass compass = { time, xCompassD, yCompassD, zCompassD, headingD , headingF};
        compassEntrys.push_back(compass);
    }
}

void DecodeGlobal::decodeGPS() {
    int64_t time = DecodeGlobal::decodeTime();

    
    uint8_t decodeSetting = 0;
    if(version == 0)
        decodeSetting = reader.readByteMax(gpsLADoubleMode[0]);

    int toRead = gpsLL_Float32?32-gpsLL_Reduction:64-gpsLL_Reduction;

    if(decodeSetting>0){
        toRead = toRead - 1 -8 -3*!gpsLL_Float32;
        if (gpsLADoubleMode[0] == 2)
        {
            switch (decodeSetting)
            {
            case 1:{
                gpsLADoubleMode[1]--; 
                break;
            }
            case 2:{
                gpsLADoubleMode[1]++;
                break;
            }
            }
        }
        
    }

    std::vector<char> xGPS = reader.readBits(toRead);

    double xGPSD = 0;
    float xGPSF = 0;

    if(gpsLL_Float32){
        xGPSF = decodeData.decode32BitsF(xGPS,gpsLL_Reduction, gpsLL_filler, gpsLADoubleMode, decodeSetting);
    }
    else{
        xGPSD = decodeData.decode64BitsD(xGPS,gpsLL_Reduction, gpsLL_filler, gpsLADoubleMode, decodeSetting);
    }

    
    decodeSetting = 0;
    if(version == 0)
        decodeSetting =  reader.readByteMax(gpsLADoubleMode[0]);
    toRead = gpsLL_Float32?32-gpsLL_Reduction:64-gpsLL_Reduction;

    if(decodeSetting>0){
        if (gpsLODoubleMode[0] == 2)
        {
            switch (decodeSetting)
            {
            case 1:{
                gpsLODoubleMode[1]--; 
                break;
            }
            case 2:{
                gpsLODoubleMode[1]++;
                break;
            }
            }
        }
        
    }

    std::vector<char> yGPS = reader.readBits(toRead);

    double yGPSD = 0;
    float yGPSF = 0;

    if(gpsLL_Float32){
        yGPSF = decodeData.decode32BitsF(yGPS, gpsLL_Reduction, gpsLL_filler, gpsLODoubleMode, decodeSetting);
    }
    else{
        yGPSD = decodeData.decode64BitsD(yGPS,gpsLL_Reduction, gpsLL_filler, gpsLODoubleMode, decodeSetting);
    }

    
    decodeSetting = 0;
    if(version == 0)
        decodeSetting = reader.readByteMax(gpsADoubleMode[0]);
    toRead = gpsA_Float32?32-gpsA_Reduction:64-gpsA_Reduction;

    if(decodeSetting>0){
        toRead = toRead - 1 -8 -3*!gpsA_Float32;
        if (gpsADoubleMode[0] == 2)
        {
            switch (decodeSetting)
            {
            case 1:{
                gpsADoubleMode[1]--; 
                break;
            }
            case 2:{
                gpsADoubleMode[1]++;
                break;
            }
            }
        }
    }

    std::vector<char> zGPS = reader.readBits(toRead);

    double zGPSD = 0;
    float zGPSF = 0;

    if(gpsA_Float32){
        zGPSF = decodeData.decode32BitsF(xGPS, gpsA_Reduction, gpsA_filler, gpsADoubleMode, decodeSetting);
    }
    else{
        zGPSD = decodeData.decode64BitsD(xGPS, gpsA_Reduction, gpsA_filler, gpsADoubleMode, decodeSetting);
    }

    if (!endOfFile) {
        DataElements::GPS gps = { time, xGPSD, yGPSD, zGPSD, xGPSF, yGPSF, zGPSF };
        gpsEntrys.push_back(gps);
    }
}

void DecodeGlobal::decodeMarker(){
    int64_t time = DecodeGlobal::decodeTime();

    markerEntrys.push_back(time);

}

void DecodeGlobal::writeToDisk() {
    //write CSV
    std::cout<<"Overall: "<<headingevents<<std::endl;
    std::cout<<"DoublemodeUse: "<<doubleModeALL<<std::endl;
    std::cout<<"Same: "<<doubleSame<<std::endl;
    std::cout<<"PM1: "<<doublepm1<<std::endl;
    if (!(hrmEntrys.size() != 0 || barometerEntrys.size() != 0 || accelerometerEntrys.size() != 0 ||
        magnitudeEntrys.size() != 0 || compassEntrys.size() != 0 || gpsEntrys.size() != 0||gloveEntrys.size() != 0)) {
            cout<<"No valid data to write found\n";
            return;
        }
    try
    {

        // erstelle ordner verzeichnisse
        fs::path path = fs::weakly_canonical(fs::path(localPathString)).parent_path();

        //create folder for the supervisor
        if(folderSupervisor) {
            path = path / supervisor;
            fs::create_directory(path);
        }
        // create folder for subject
        if(folderSubject){
            path = path / subject;
            fs::create_directory(path);
        }
        // create folder for date
        std::stringstream ss;
        struct tm timeRepresentation;

        // Convert to local time.
        localtime_r(&timeDec,&timeRepresentation);

        ss << std::put_time(&timeRepresentation, "%Y-%m-%d_%H-%M");
        string timeFolder = ss.str();
            
        if(folderDate){
            path = path / timeFolder;

            fs::create_directory(path);
        }
        stringstream filenamebase;

        if (filenameSupervisor)//display supervisor name
        {
            filenamebase << supervisor << "_";
        }
        if (filenameSubject)// display subject
        {
            filenamebase << subject << "_";
        }
        if (filenameDate)// display time
        {
            filenamebase << timeFolder << "_";
        }

        if (gloveEntrys.size() > 0) {

            stringstream filename;

            filename << filenamebase.str() << "glove.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time ; X0; Y0; Z0; X1; Y1; Z1; X2; Y2; Z2; X3; Y3; Z3; X4; Y4; Z4; X5; Y5; Z5;\n";

            for (int i = 0; i < gloveEntrys.size(); i = i+1)
            {
                DataElements::GloveData entry = gloveEntrys[i];

                outputFile << entry.time << " ; " << entry.single0x << " ; " << entry.single0y << " ; " << entry.single0z << " ; " << entry.single1x << " ; " << entry.single1y << " ; " << entry.single1z << " ; "  << entry.single2x << " ; " << entry.single2y << " ; " << entry.single2z << " ; "  << entry.single3x << " ; " << entry.single3y << " ; " << entry.single3z << " ; "  << entry.single4x << " ; " << entry.single4y << " ; " << entry.single4z << " ; "  << entry.single5x << " ; " << entry.single5y << " ; " << entry.single5z << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        if (hrmEntrys.size() > 0) {

            stringstream filename;

            filename << filenamebase.str() << "hrm.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time ; PPG \n";

            for (int i = 0; i < hrmEntrys.size(); i++)
            {
                DataElements::HRM entry = hrmEntrys[i];

                outputFile << entry.time << " ; " << entry.ppgVal << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        if (barometerEntrys.size() > 0) {

            stringstream filename;

            filename << filenamebase.str() << "barometer.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time ; Temperature ; Pressure ;  Altitude \n";

            for (int i = 0; i < barometerEntrys.size(); i++)
            {
                DataElements::Barometer entry = barometerEntrys[i];

                string temperature = temperature_Float32?std::to_string(entry.temperatureF):std::to_string(entry.temperatureD);
                string pressure = pressure_Float32?std::to_string(entry.pressureF):std::to_string(entry.pressureD);
                string height = std::to_string(entry.heightD);
                if(writeAltitude && heigth_Float32){
                    height = std::to_string(entry.heightF);
                }
                

                outputFile << entry.time << " ; " << temperature  << " ; " << pressure << " ; " << height << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        if (accelerometerEntrys.size() > 0) {

            stringstream filename;

            filename << filenamebase.str() << "accelerometer.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time ; x ; y ;  z\n";

            for (int i = 0; i < accelerometerEntrys.size(); i++)
            {
                DataElements::Accelerometer entry = accelerometerEntrys[i];

                outputFile << entry.time << " ; " << entry.x << " ; " << entry.y << " ; " << entry.z << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        if (magnitudeEntrys.size() > 0) {

            stringstream filename;

            filename << filenamebase.str() << "magnitude.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time ; Acceleration\n";

            for (int i = 0; i < magnitudeEntrys.size(); i++)
            {
                DataElements::Magnitude entry = magnitudeEntrys[i];

                outputFile << entry.time << " ; " << entry.magnitude << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        if (compassEntrys.size() > 0) {

            stringstream filename;

            filename << filenamebase.str() << "compass.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time ; x ; y ;  z ; heading\n";

            for (int i = 0; i < compassEntrys.size(); i++)
            {
                DataElements::Compass entry = compassEntrys[i];

                string heading = compassHeading_Float32?std::to_string(entry.headingF):std::to_string(entry.headingD);

                outputFile << entry.time << " ; " << entry.x << " ; " << entry.y << " ; " << entry.z << " ; " << heading << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        if (gpsEntrys.size() > 0) {

            stringstream filename;

            filename << filenamebase.str() << "gps.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time ; x ; y ;  z\n";

            for (int i = 0; i < gpsEntrys.size(); i++)
            {
                DataElements::GPS entry = gpsEntrys[i];

                string x = gpsA_Float32?std::to_string(entry.xF):std::to_string(entry.xD);
                string y = gpsA_Float32?std::to_string(entry.yF):std::to_string(entry.yD);
                string z = gpsA_Float32?std::to_string(entry.zF):std::to_string(entry.zD);

                outputFile << entry.time << " ; " << x << " ; " << y << " ; " << z << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        if(markerEntrys.size()>0){
            stringstream filename;

            filename << filenamebase.str() << "marker.csv";

            fs::path filepath = path / filename.str();
            ofstream outputFile(filepath);

            outputFile << "Time\n";

            for (int i = 0; i < markerEntrys.size(); i++)
            {
                int64_t entry = markerEntrys[i];
                outputFile << entry << "\n";
            }

            outputFile.flush();
            outputFile.close();
            std::flush(outputFile);
        }

        cout << "Files saved to: " << path <<"\n";

    }
    catch (const std::exception& e)
    {
        cout << "Error while writing files to Disk: " << e.what();
    }
}
