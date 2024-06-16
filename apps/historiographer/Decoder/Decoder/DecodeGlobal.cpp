#include "DecodeGlobal.h"
#include "../pugixml/src/pugixml.hpp"


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
        }
        else
        {
            //End of IDs
            getIDs = false;
            idMap map = { localID,0 };

            idMapping.push_back(map);
        }

    }

    writeAltitude = reader.readByteMax(1) & 1;

    jsMath = reader.readByteMax(1) & 1;

    saveXML = reader.readByteMax(1) & 1;


    filenameSupervisor = reader.readByteMax(1) & 1;
    filenameSubject = reader.readByteMax(1) & 1;
    filenameDate = reader.readByteMax(1) & 1;

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

    std::cout << "Supervisor: " << supervisor << "\n";
    std::cout << "Subject: " << subject << "\n";
    std::cout << "Sensors: " << int(idMapping.size() - 1) << "\n";
    std::cout << "Save Height: " << int(writeAltitude) << "\n";
    std::cout << "Save XML: " << int(saveXML) << "\n";
    std::cout << "Date: " << int(day) << "." << int(month) + 1 << "." << int(yearReal) << " at: " << int(hours) << ":" << int(minutes) << "\n";
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
        //Magnetude
        decodeMagnetude();
        break;
    case 5:
        //Compass
        decodeCompass();
        break;
    case 6:
        //GPS
        decodeGPS();
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

int DecodeGlobal::decodeTime() {
    unsigned char longDeltatime = reader.readByteMax(1);
    int time = 0;
    if (longDeltatime == 0) {
        time = unsigned char(reader.readByteMax(8));
    }
    else {
        std::vector<char> timeAsChar = reader.readBits(32);

        for (int i = 0; i < 4; i++)
        {
            time = time << 8;
            time = time | unsigned char(timeAsChar[i]);
        }
    }
    lastTimestamp = lastTimestamp + time;
    return lastTimestamp;
}

void DecodeGlobal::decodeHRM() {
    int time = DecodeGlobal::decodeTime();

    std::vector<char> ppg = reader.readBits(12);
    int ppgD = 0;
    char* p = (char*)&ppgD;

    *(p) = ppg[0];
    bool bit = false;

    unsigned char lasteEntry = ppg[1];
    for (int i = 0; i < 4; i++)
    {
        ppgD = ppgD << 1;
        bit = lasteEntry & 128;
        ppgD = ppgD | bit;
        lasteEntry = lasteEntry << 1;
    }

    if (!endOfFile) {
        DataElements::HRM hrm = { time, ppgD };
        hrmEntrys.push_back(hrm);
    }
}

void DecodeGlobal::decodeBarometer() {
    int time = DecodeGlobal::decodeTime();
    std::vector<char> temp = reader.readBits(64);

    double tempD = 0;

    char* p = (char*)&tempD;

    for (int i = 0; i < 8; i++)
    {
        *(p + i) = temp[i];
    }
    std::vector<char> press = reader.readBits(64);

    double pressD = 0;

    p = (char*)&pressD;

    for (int i = 0; i < 8; i++)
    {
        *(p + i) = press[i];
    }

    double altitudeD = 0;

    if (writeAltitude) {
        std::vector<char> altitude = reader.readBits(64);

        p = (char*)&altitudeD;

        for (int i = 0; i < 8; i++)
        {
            *(p + i) = altitude[i];
        }
    }
    else {
        if (jsMath) {
            double multiplicantBangle = (1.0 - BangleJsMath::jswrap_math_pow((pressD / 1013.25), 0.1903));
            altitudeD = 44330 * multiplicantBangle;
        }
        else
        {
            double multiplicant = (1 - pow((pressD / 1013.25), (1 / 5.255)));
            altitudeD = 44330 * multiplicant;
        }
    }

    if (!endOfFile) {
        DataElements::Barometer barometer = { time, tempD,pressD,altitudeD };
        barometerEntrys.push_back(barometer);
    }
}

void DecodeGlobal::decodeAccelerometer() {
    int time = DecodeGlobal::decodeTime();
    if (time == 3092) {
        std::cout << "";
    }

    // get data from Array

    bool positiv = reader.readByteMax(1);

    std::vector<char> xAccel = reader.readBits(16);

    int xAccelD = 0;
    xAccelD = xAccelD | unsigned char(xAccel[0]);
    xAccelD = xAccelD << 8;
    xAccelD = xAccelD | unsigned char(xAccel[1]);
    if (positiv == false) {
        xAccelD = -xAccelD;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> yAccel = reader.readBits(16);

    int yAccelD = 0;
    yAccelD = yAccelD | unsigned char(yAccel[0]);
    yAccelD = yAccelD << 8;
    yAccelD = yAccelD | unsigned char(yAccel[1]);
    if (positiv == false) {
        yAccelD = -yAccelD;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> zAccel = reader.readBits(16);

    int zAccelD = 0;
    zAccelD = zAccelD | unsigned char(zAccel[0]);
    zAccelD = zAccelD << 8;
    zAccelD = zAccelD | unsigned char(zAccel[1]);
    if (positiv == false) {
        zAccelD = -zAccelD;
    }

    //convert Data back to double
    double xAccelerometerData = xAccelD / 8192.0;
    double yAccelerometerData = yAccelD / 8192.0;
    double zAccelerometerData = zAccelD / 8192.0;



    if (!endOfFile) {
        DataElements::Accelerometer accel = { time, xAccelerometerData , yAccelerometerData , zAccelerometerData };
        accelerometerEntrys.push_back(accel);
    }
}

void DecodeGlobal::decodeMagnetude() {
    int time = DecodeGlobal::decodeTime();

    bool positiv = reader.readByteMax(1);

    std::vector<char> magnetude = reader.readBits(16);

    int magnetudeD = 0;
    magnetudeD = magnetudeD | unsigned char(magnetude[0]);
    magnetudeD = magnetudeD << 8;
    magnetudeD = magnetudeD | unsigned char(magnetude[1]);


    if (positiv == false) {
        magnetudeD = -magnetudeD;
    }

    //convert Data back to double
    double magnetudeData = magnetudeD / 8192.0;

    if (!endOfFile) {
        DataElements::Magnetude mag = { time, magnetudeData };
        magnetudeEntrys.push_back(mag);
    }

}

void DecodeGlobal::decodeCompass() {
    int time = DecodeGlobal::decodeTime();

    bool positiv = reader.readByteMax(1);

    std::vector<char> xCompass = reader.readBits(12);
    int xCompassD = 0;
    char* p = (char*)&xCompassD;

    *(p) = unsigned char(xCompass[0]);
    bool bit = false;

    unsigned char lasteEntry = xCompass[1];
    for (int i = 0; i < 4; i++)
    {
        xCompassD = xCompassD << 1;
        bit = lasteEntry & 128;
        xCompassD = xCompassD | bit;
        lasteEntry = lasteEntry << 1;
    }
    if (positiv == false) {
        xCompassD = -xCompassD;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> yCompass = reader.readBits(12);
    int yCompassD = 0;
    p = (char*)&yCompassD;

    *(p) = unsigned char(yCompass[0]);

    lasteEntry = yCompass[1];
    for (int i = 0; i < 4; i++)
    {
        yCompassD = yCompassD << 1;
        bit = lasteEntry & 128;
        yCompassD = yCompassD | bit;
        lasteEntry = lasteEntry << 1;
    }
    if (positiv == false) {
        yCompassD = -yCompassD;
    }

    positiv = reader.readByteMax(1);

    std::vector<char> zCompass = reader.readBits(12);
    int zCompassD = 0;
    p = (char*)&zCompassD;

    *(p) = unsigned char(zCompass[0]);

    lasteEntry = zCompass[1];
    for (int i = 0; i < 4; i++)
    {
        zCompassD = zCompassD << 1;
        bit = lasteEntry & 128;
        zCompassD = zCompassD | bit;
        lasteEntry = lasteEntry << 1;
    }
    if (positiv == false) {
        zCompassD = -zCompassD;
    }


    std::vector<char> heading = reader.readBits(64);

    double headingD = 0;

    //make char pointer of headingD for decoding
    p = (char*)&headingD;

    for (int i = 0; i < 8; i++)
    {
        *(p + i) = heading[i];
    }

    if (!endOfFile) {
        DataElements::Compass compass = { time, xCompassD, yCompassD, zCompassD, headingD };
        compassEntrys.push_back(compass);
    }
}

void DecodeGlobal::decodeGPS() {
    int time = DecodeGlobal::decodeTime();

    std::vector<char> xGPS = reader.readBits(64);

    double xGPSD = 0;

    char* p = (char*)&xGPSD;

    for (int i = 0; i < 8; i++)
    {
        *(p + i) = xGPS[i];
    }

    std::vector<char> yGPS = reader.readBits(64);

    double yGPSD = 0;

    p = (char*)&yGPSD;

    for (int i = 0; i < 8; i++)
    {
        *(p + i) = yGPS[i];
    }

    std::vector<char> zGPS = reader.readBits(64);

    double zGPSD = 0;

    p = (char*)&zGPSD;

    for (int i = 0; i < 8; i++)
    {
        *(p + i) = zGPS[i];
    }

    if (!endOfFile) {
        DataElements::GPS gps = { time, xGPSD, yGPSD, zGPSD };
        gpsEntrys.push_back(gps);
    }
}

void DecodeGlobal::writeToDisk() {
    if (saveXML) {
        bool decodingHRM = hrmEntrys.size() != 0;
        bool decodingBarometer = barometerEntrys.size() != 0;
        bool decodingAccelerometer = accelerometerEntrys.size() != 0;
        bool decodingMagnetude = magnetudeEntrys.size() != 0;
        bool decodingCompass = compassEntrys.size() != 0;
        bool decodingGps = gpsEntrys.size() != 0;

        int hrmSize = hrmEntrys.size();
        int currentHRM = 0;

        int barometerSize = barometerEntrys.size();
        int currentbarometer = 0;

        int accelerometerSize = accelerometerEntrys.size();
        int currentAccelerometer = 0;

        int magnetudeSize = magnetudeEntrys.size();
        int currentMagnetude = 0;

        int compassSize = compassEntrys.size();
        int currentCompass = 0;

        int gpsSize = gpsEntrys.size();
        int currentGPS = 0;
        
        int idTowrite;

        pugi::xml_document out;

        pugi::xml_node top = out.append_child("Events");

        while (decodingHRM || decodingBarometer || decodingAccelerometer || decodingMagnetude || decodingCompass || decodingGps) {

            time_t lowestTime = NULL;

            if (decodingHRM) {
                DataElements::HRM compare = hrmEntrys[currentHRM];
                lowestTime = compare.time;
                idTowrite = 1;
            }
            if (decodingBarometer) {
                DataElements::Barometer compare = barometerEntrys[currentbarometer];
                if (lowestTime == NULL) {
                    lowestTime = compare.time;
                    idTowrite = 2;
                }
                else
                {
                    if (lowestTime > compare.time)
                    {
                        lowestTime = compare.time;
                        idTowrite = 2;
                    }
                }
            }
            if (decodingAccelerometer) {
                DataElements::Accelerometer compare = accelerometerEntrys[currentAccelerometer];
                if (lowestTime == NULL) {
                    lowestTime = compare.time;
                    idTowrite = 3;
                }
                else
                {
                    if (lowestTime > compare.time)
                    {
                        lowestTime = compare.time;
                        idTowrite = 3;
                    }
                }
            }
            if (decodingMagnetude) {
                DataElements::Magnetude compare = magnetudeEntrys[currentMagnetude];
                if (lowestTime == NULL) {
                    lowestTime = compare.time;
                    idTowrite = 4;
                }
                else
                {
                    if (lowestTime > compare.time)
                    {
                        lowestTime = compare.time;
                        idTowrite = 4;
                    }
                }
            }
            if (decodingCompass) {
                DataElements::Compass compare = compassEntrys[currentCompass];
                if (lowestTime == NULL) {
                    lowestTime = compare.time;
                    idTowrite = 5;
                }
                else
                {
                    if (lowestTime > compare.time)
                    {
                        lowestTime = compare.time;
                        idTowrite = 5;
                    }
                }
            }
            if (decodingGps) {
                DataElements::GPS compare = gpsEntrys[currentGPS];
                if (lowestTime == NULL) {
                    lowestTime = compare.time;
                    idTowrite = 6;
                }
                else
                {
                    if (lowestTime > compare.time)
                    {
                        lowestTime = compare.time;
                        idTowrite = 6;
                    }
                }
            }

            switch (idTowrite)
            {
            case 1:
                xmlHRM(hrmEntrys[currentHRM], top);
                currentHRM++;

                if (currentHRM == hrmEntrys.size()) {
                    decodingHRM = false;
                }

                break;

            case 2:
                xmlBarometer(barometerEntrys[currentbarometer], top);
                currentbarometer++;

                if (currentbarometer == barometerEntrys.size()) {
                    decodingBarometer = false;
                }

                break;

            case 3:
                xmlAccelerometer(accelerometerEntrys[currentAccelerometer], top);
                currentAccelerometer++;

                if (currentAccelerometer == accelerometerEntrys.size()) {
                    decodingAccelerometer = false;
                }

                break;

            case 4:
                xmlMagnetude(magnetudeEntrys[currentMagnetude], top);
                currentMagnetude++;

                if (currentMagnetude == magnetudeEntrys.size()) {
                    decodingMagnetude = false;
                }

                break;

            case 5:
                xmlCompass(compassEntrys[currentCompass], top);
                currentCompass++;

                if (currentCompass == compassEntrys.size()) {
                    decodingCompass = false;
                }

                break;

            case 6:
                xmlGPS(gpsEntrys[currentGPS], top);
                currentGPS++;

                if (currentGPS == gpsEntrys.size()) {
                    decodingGps = false;
                }

                break;

            default:
                break;
            }
        };



        // erstelle ordner verzeichnisse
        fs::path path = fs::weakly_canonical(fs::path(localPathString)).parent_path();

        //create folder for the supervisor
        path = path / supervisor;
        fs::create_directory(path);

        // create folder for subject
        path = path / subject;
        fs::create_directory(path);

        // create folder for date
        std::stringstream ss;
        struct tm timeRepresentation;

        // Convert to local time.
        errno_t err = localtime_s(&timeRepresentation, &timeDec);
        if (err)
        {
            printf("Invalid argument to _localtime64_s.");
            exit(1);
        }


        ss << std::put_time(&timeRepresentation, "%Y-%m-%d_%H-%M");
        string timeFolder = ss.str();
        path = path / timeFolder;

        fs::create_directory(path);

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

        filenamebase<<"Events.xml";
        path = path / filenamebase.str();

        out.save_file(path.c_str());
        cout << "File saved under: " << path;

    }
    else
    {
        //write CSV
        if (hrmEntrys.size() != 0 || barometerEntrys.size() != 0 || accelerometerEntrys.size() != 0 ||
            magnetudeEntrys.size() != 0 || compassEntrys.size() != 0 || gpsEntrys.size() != 0) {
            try
            {

                // erstelle ordner verzeichnisse
                fs::path path = fs::weakly_canonical(fs::path(localPathString)).parent_path();

                //create folder for the supervisor
                path = path / supervisor;
                fs::create_directory(path);

                // create folder for subject
                path = path / subject;
                fs::create_directory(path);

                // create folder for date
                std::stringstream ss;
                struct tm timeRepresentation;

                // Convert to local time.
                errno_t err = localtime_s(&timeRepresentation, &timeDec);
                if (err)
                {
                    printf("Invalid argument to _localtime64_s.");
                    exit(1);
                }


                ss << std::put_time(&timeRepresentation, "%Y-%m-%d_%H-%M");
                string timeFolder = ss.str();
                path = path / timeFolder;

                fs::create_directory(path);

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

                        outputFile << entry.time << " ; " << entry.temperature << " ; " << entry.pressure << " ; " << entry.height << "\n";
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

                if (magnetudeEntrys.size() > 0) {

                    stringstream filename;

                    filename << filenamebase.str() << "magnetude.csv";

                    fs::path filepath = path / filename.str();
                    ofstream outputFile(filepath);

                    outputFile << "Time ; Acceleration\n";

                    for (int i = 0; i < magnetudeEntrys.size(); i++)
                    {
                        DataElements::Magnetude entry = magnetudeEntrys[i];

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

                        outputFile << entry.time << " ; " << entry.x << " ; " << entry.y << " ; " << entry.z << " ; " << entry.heading << "\n";
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

                        outputFile << entry.time << " ; " << entry.x << " ; " << entry.y << " ; " << entry.z << "\n";
                    }

                    outputFile.flush();
                    outputFile.close();
                    std::flush(outputFile);
                }

                cout << "Files saved to: " << path;

            }
            catch (const std::exception& e)
            {
                cout << "Error while writing files to Disk: " << e.what();
            }
        }
    }
}


void DecodeGlobal::xmlHRM(DataElements::HRM hrm, pugi::xml_node head)
{
    pugi::xml_node hrmXML = head.append_child("HRM");
    pugi::xml_attribute time_attribute = hrmXML.append_attribute("time");
    time_t timeStamp = hrm.time;
    intmax_t timeInt = (intmax_t)timeStamp;


    std::stringstream ss;
    ss << timeInt;

    time_attribute.set_value(ss.str().c_str());

    pugi::xml_node ppgnode = hrmXML.append_child("PPG");
    ppgnode = ppgnode.append_child(pugi::node_pcdata);
    ppgnode.set_value(std::to_string(hrm.ppgVal).c_str());
}

void DecodeGlobal::xmlBarometer(DataElements::Barometer barometer, pugi::xml_node head)
{
    pugi::xml_node barometerXML = head.append_child("Barometer");
    pugi::xml_attribute time_attribute = barometerXML.append_attribute("time");
    time_t timeStamp = barometer.time;
    intmax_t timeInt = (intmax_t)timeStamp;

    std::stringstream ss;
    ss << timeInt;

    time_attribute.set_value(ss.str().c_str());

    pugi::xml_node node = barometerXML.append_child("Temperature");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(barometer.temperature).c_str());

    node = barometerXML.append_child("Pressure");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(barometer.pressure).c_str());

    node = barometerXML.append_child("Height");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(barometer.height).c_str());
}

void DecodeGlobal::xmlAccelerometer(DataElements::Accelerometer accelerometer, pugi::xml_node head)
{
    pugi::xml_node accelerometerXML = head.append_child("Accelerometer");
    pugi::xml_attribute time_attribute = accelerometerXML.append_attribute("time");
    time_t timeStamp = accelerometer.time;
    intmax_t timeInt = (intmax_t)timeStamp;

    std::stringstream ss;
    ss << timeInt;

    time_attribute.set_value(ss.str().c_str());

    pugi::xml_node node = accelerometerXML.append_child("X");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(accelerometer.x).c_str());

    node = accelerometerXML.append_child("Y");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(accelerometer.y).c_str());

    node = accelerometerXML.append_child("Z");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(accelerometer.z).c_str());
}

void DecodeGlobal::xmlMagnetude(DataElements::Magnetude magnetude, pugi::xml_node head)
{
    pugi::xml_node magnetudeXML = head.append_child("Magnetude");
    pugi::xml_attribute time_attribute = magnetudeXML.append_attribute("time");
    time_t timeStamp = magnetude.time;
    intmax_t timeInt = (intmax_t)timeStamp;

    std::stringstream ss;
    ss << timeInt;

    time_attribute.set_value(ss.str().c_str());

    pugi::xml_node node = magnetudeXML.append_child("Magnetude");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(magnetude.magnitude).c_str());
}

void DecodeGlobal::xmlCompass(DataElements::Compass compass, pugi::xml_node head)
{
    pugi::xml_node compassXML = head.append_child("Compass");
    pugi::xml_attribute time_attribute = compassXML.append_attribute("time");
    time_t timeStamp = compass.time;
    intmax_t timeInt = (intmax_t)timeStamp;

    std::stringstream ss;
    ss << timeInt;

    time_attribute.set_value(ss.str().c_str());

    pugi::xml_node node = compassXML.append_child("X");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(compass.x).c_str());

    node = compassXML.append_child("Y");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(compass.y).c_str());

    node = compassXML.append_child("Z");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(compass.z).c_str());

    node = compassXML.append_child("Heading");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(compass.heading).c_str());

}

void DecodeGlobal::xmlGPS(DataElements::GPS gps, pugi::xml_node head)
{
    pugi::xml_node gpsXML = head.append_child("GPS");
    pugi::xml_attribute time_attribute = gpsXML.append_attribute("time");
    time_t timeStamp = gps.time;
    intmax_t timeInt = (intmax_t)timeStamp;

    std::stringstream ss;
    ss << timeInt;

    time_attribute.set_value(ss.str().c_str());

    pugi::xml_node node = gpsXML.append_child("X");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(gps.x).c_str());

    node = gpsXML.append_child("Y");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(gps.y).c_str());

    node = gpsXML.append_child("Z");
    node = node.append_child(pugi::node_pcdata);
    node.set_value(std::to_string(gps.z).c_str());

}


