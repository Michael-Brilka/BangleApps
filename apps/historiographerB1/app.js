var showClock = false;
var showDate = false;
var updateDate = false;

var oldHour = -1;
g.setFont("6x8", 5);
g.setFontAlign(0, 0);

var drawTimeout;

function drawClock() {
  "ram"
  "jit"
  var date = new Date();
  var hours = date.getHours();
  if (oldHour != hours) {
    g.drawString(`${hours}:`, 63, 60, true);
    g.setColor(g.theme.bg)
    g.fillRect(100, 40, 165, 80);
    g.setColor(g.theme.fg)
    oldHour = hours;
  }
  g.drawString(date.getMinutes(), 133, 60, true);
}

var dateTimeout;
var timeoutCalc;

function drawUpdateableDate() {
  var d = new Date();
  g.drawString(`${d.getFullYear()}-${d.getMonth()+1}-${d.getDate()}`, 88, 120, true);
  if (dateTimeout) clearTimeout(dateTimeout);
  var hours = 24 - d.getHours();
  var minutes = 60 - d.getMinutes();
  timeoutCalc = (((hours * 60) + minutes) * 60000);
  dateTimeout = setTimeout(function() {
    if (dateTimeout != null) {
      dateTimeout = undefined;
      drawUpdateableDate();
    }
  }, timeoutCalc);
}

function drawStaticDate() {
  var d = new Date();
  g.drawString(`${d.getDate()} ${d.toString().split(" ")[1]}`, 88, 110, true);
  g.drawString(`${d.getFullYear()}`, 88, 150, true);
}

function drawFaceScreen() {
  g.setFont("6x8", 5);
  g.setFontAlign(0, 0);
  if (showClock) {
    drawClock();
    drawTimeout = setInterval(drawClock, 60000);
  }
  if (showDate) {
    g.setFont("6x8", 5);
    g.setFontAlign(0, 0);
    if (updateDate) {
      drawUpdateableDate();
    } else {
      drawStaticDate();
    }
  }
}
let powersavingGPS = false;
let gpsTurnOnIntervallFunction;
let gpsFloat32 = false;
let noMoreStorage = false;

let appID = "historio";
let historiographer = E.compiledC(`
  // void initArray(int, int)
  // void clear()
  // void writeIDs()
  // void setHRM(bool)
  // void setAccelerometer(bool, int)
  // void setMagnetude(bool, int)
  // void setCompass(bool, bool, int)
  // void setGPS(bool, bool)
  // void setGPSaddresses(int, int, int)
  // bool writeIDsToArray()
  // bool namingOutputFile(bool, bool, bool)
  // bool writeDate(int, int, int)
  // bool writeTime(int, int)
  // bool writeHRM(int, int)
  // bool writeAccelerometer(int,int,int,int)
  // bool writeMagnetude(int, int)
  // bool writeCompass(int, int, int, int)
  // bool writeGPS(int)
  // void writeToArray()
  // void writeBit(bool)
  // void writeNBits(int,int)
  // void writeNBitsNoShift(int,int) 
  // void writeByte(int)
  // void writePreamble(int, int)
  // void writeDouble(int, bool)
  // bool hitLimit()
  // int getLimit() 
  // int getByteWrite() 
  // int getbyteIndex() 
  // int getArrayIndex(int) 


  /***
  Local variables
  ***/
  //writeBuffer and the index
  unsigned char byteWrite = 0;
  unsigned char byteIndex = 0;

  //Array and information
  unsigned char* array;
  int index = 0;
  int maxIndex = 0;

  unsigned char overflowArray[30];
  int indexOverflow = 0;
  
  //Local ID encoding 
  char localIDLength = 0;
  char localHRMID = 0;
  char localAccelID = 0;
  char localMagnetudeID = 0;
  char localCompassID = 0;
  char localGPSID = 0;

  //is sensor used?
  bool localHRMUse = 0;
  bool localAccelUse = 0;
  bool localMagnetudeUse = 0;
  bool localCompassUse = 0;
  bool localGPSUse = 0;

  //sensor values as pointers
  unsigned char range;
 
  unsigned char accelRange;
  
  unsigned char* heading;
  bool headingFloat32 = 0;

  unsigned char* xGPS;
  unsigned char* yGPS;
  unsigned char* zGPS;
  bool gpsFloat32 = 0;

  /***
  This function sets up all the nessesery data for the module.

  This function sets the pointer to the write array. This pointer is recived from the JS side.
  Additionaly the maximum Index needs to be set.

  For the module to work properly this initArray function must be called first!
  ***/
  void initArray(unsigned char *arrayPointer, int dataMaxIndex){
    array = arrayPointer;
    maxIndex = dataMaxIndex;
  }

  /***
  This function writes the data from the writeBuffer to the Array.

  This function writes the data from the writeBuffer to the Array, while resetting all associated variables. 
  If the writeBuffer is bigger than 254 the last bit will be read out of the writeBuffer and replaced with a 0.
  The leftover bit will then be inserted again in the writeBuffer.
  This is done because the value 255 shouldnt be written to the file. As this indecates erased flash memory.
  https://www.espruino.com/ReferenceBANGLEJS2#t_StorageFile

  ***/
  void writeToArray(){
    if(index < maxIndex){
      if(byteWrite <254){
        array[index] = byteWrite;
        index++;  
        byteWrite = 0;
        byteIndex = 0;
      }
      else{
        bool lastBit = byteWrite & 1;
        array[index] = byteWrite & 254;
        index++;
        byteWrite = lastBit;
        byteWrite = byteWrite << 1;
        byteIndex = 1;
      }
    }
    else{
      // else write to overflow
      if(byteWrite < 254){
        overflowArray[indexOverflow] = byteWrite;
        indexOverflow++;  
        byteWrite = 0;
        byteIndex = 0;
      }
      else{
        bool lastBit = byteWrite & 1;
        overflowArray[indexOverflow] = byteWrite & 254;
        indexOverflow++;
        byteWrite = lastBit;
        byteWrite = byteWrite << 1;
        byteIndex = 1;
      }
    }

  }

  /***
  This function checks if the current index is bigger than the max Index.
  This indecates that the array needs to be written to the file.
  ***/
  bool hitLimit(){
    if(index == maxIndex){
      return true;
    }  
    else
    {
      return false;
    }
  }

  /***
  This function writes a single bit to the writeBuffer.
  If the writeBuffer is full then write the writeBuffer to the array, otherwise left shift the array by one.
  ***/
  void writeBit(bool toWrite){
    byteWrite = byteWrite | toWrite;
    byteIndex ++;
    if (byteIndex == 8) {
          writeToArray();
      }
      else{

          byteWrite = byteWrite << 1;
      }
  }

  /***
  This function writes multiple bits to the writeBuffer.

  This function first shifts the data to the left, so that the bits are all left aligned.
  After that the MSB bit will be read and written to the writeBuffer,
  the data then will be shifted to the left. This is repeated numberOfBit times.
  ***/
  void writeNBits(unsigned char writeData, int numberOfBits){
    for(int i = numberOfBits ; i<8;i++){
          writeData = writeData << 1;
      }

    for (int i = 0; i < numberOfBits; i++) {
          bool bitToWrite = writeData & 128;
          writeBit(bitToWrite);
          writeData = writeData << 1;
      }
  }

  //same as writeNBits but without shifting the data left.
  void writeNBitsNoShift(unsigned char writeData, int numberOfBits){
    for (int i = 0; i < numberOfBits; i++) {
          bool bitToWrite = writeData & 128;
          writeBit(bitToWrite);
          writeData = writeData << 1;
      }
  }
  /***
  This function writes a byte to the writeBuffer.
  Starting from the MSB bit.
  ***/
  void writeByte(unsigned char writeData){

    for (int i = 0; i < 8; i++) {
          bool bitToWrite = writeData & 128;
          writeBit(bitToWrite);
          writeData = writeData << 1;
      }
  }

  /***
  This function writes the preamble for the data.
  The preamble contains of the localID as well as the deltatime between the each timestamp.
  ***/
  void writePreamble(unsigned char id, int deltatime){
      writeNBits(id, localIDLength);
    if(deltatime < 255){
      writeBit(false);
      char dt = char(deltatime);
      writeByte(dt);
    }else{
      writeBit(true);
      unsigned char byte0 = deltatime & 0xFF;
      deltatime = deltatime >> 8;
      unsigned char byte1 = deltatime & 0xFF;
      deltatime = deltatime >> 8;
      unsigned char byte2 = deltatime & 0xFF;
      deltatime = deltatime >> 8;
      unsigned char byte3 = deltatime & 0xFF;
      writeByte(byte3);
      writeByte(byte2);
      writeByte(byte1);
      writeByte(byte0);
    }
  }

  /***
  This function writes a double value to the writeBuffer.
  ***/
  void writeDouble(unsigned char* doubleVal, bool useFloat32){
    for(int i = 0; i < (8-(4*useFloat32)); i++){
      writeByte(doubleVal[i]);
    }
  }

  /***
  This function writes clears the index because the array has been saved to a file.
  ***/
  void clear(){
    index = 0;

    for(; index < indexOverflow; index++){
      array[index] = overflowArray[index];
    }
    indexOverflow = 0;

  }

  /***
  These functions mark if the will be written to a file.
  ***/
  void setHRM(bool state){
    localHRMUse = state;
  }
  void setAccelerometer(bool state, int range){
    localAccelUse = state;
    accelRange = range;
  }
  void setMagnetude(bool state, int range){
    localMagnetudeUse = state;
    accelRange = range;
  }
  void setCompass(bool state, bool compassHeadingF32, unsigned char* heading_){
    localCompassUse = state;
    headingFloat32 = compassHeadingF32;
    heading = heading_;
  }
  void setGPS(bool state, bool gpsF32){
    localGPSUse = state;
    gpsFloat32 = gpsF32;
  }
  void setGPSaddresses(unsigned char* xGPS_, unsigned char* yGPS_, unsigned char* zGPS_){
    xGPS = xGPS_;
    yGPS = yGPS_;
    zGPS = zGPS_;
  }
  /***
  This function checks if the given Sensor should be used and it gives a localID to the Sensor.
  The localID calculation ensures that the ID field is only as long as needed. 
  ***/
  void writeIDs(){
    char id = 0;
    if(localHRMUse == 1){
      localHRMID = id;
      id++;
    }
    if(localAccelUse == 1){
      localAccelID = id;
      id++;
    }
    if(localMagnetudeUse == 1){
      localMagnetudeID = id;
      id++;
    }
    if(localCompassUse == 1){
      localCompassID = id;
      id++;
    }
    if(localGPSUse == 1){
      localGPSID = id;
      id++;
    }

    while (id > 0) {
          localIDLength++;
          id >>= 1;
    }
  }

  /***
  This function writes all localIDs with the globalIDs to the file.
  This is needed for the decoding to remap all sensors.

  It returns if the array is full.
  ***/
  bool writeIDsToArray(){
    writeIDs();
    writeByte(localIDLength);
    if(localHRMUse != 0){
      writeNBits(localHRMID, localIDLength);
      writeByte(1);
    }
    if(localAccelUse != 0){
      writeNBits(localAccelID, localIDLength);
      writeByte(3);

      writeNBits(accelRange,2);
    }
    if(localMagnetudeUse != 0){
      writeNBits(localMagnetudeID, localIDLength);
      writeByte(4);

      if(localAccelUse == 0){
        writeNBits(accelRange,2);
      }
    }
    if(localCompassUse != 0){
      writeNBits(localCompassID, localIDLength);
      writeByte(5);

      writeBit(headingFloat32);
    }
    if(localGPSUse != 0){
      writeNBits(localGPSID, localIDLength);
      writeByte(6);

      writeBit(gpsFloat32);
	}

    writeNBits(255, localIDLength);

    if(index >= maxIndex-1){
      return true;
    }  
    else
    {
      return false;
    }
  }


  /***
  This function writes the options for decoding.
  Indicates how the outputfile should be named.

  It returns if the array is full.
  ***/
  bool namingOutputFile(bool filenameSupervisor,bool filenameSubject, bool filenameDate){
    writeBit(filenameSupervisor);
    writeBit(filenameSubject);
    writeBit(filenameDate);

    if(index >= maxIndex-1){
      return true;
    }  
    else
    {
      return false;
    }
  }


  /***
  This function writes the current Date to the file.

  It returns if the array is full.
  ***/
  bool writeDate(int year, int month, int day){

    char numberOfBitsYear = 0;
    int yearCopy = year;

    while (yearCopy > 0) {
      numberOfBitsYear++;
      yearCopy >>= 1;
    }

    writeByte(numberOfBitsYear);
      bool write = false;
      for(int i = 0; i < numberOfBitsYear; i++){
      write = year & 1;
      writeBit(write);
      year = year >> 1;
    }

    writeNBits(month, 4);
    writeNBits(day -1, 5);

    return hitLimit();
  }


  /***
  This function writes the current time to the file.

  It returns if the array is full.
  ***/
  bool writeTime(char hours, char minutes){
    writeNBits(hours, 5);
    writeNBits(minutes , 6);
    return hitLimit();
  }

  /***
  This function writes the ppg value to the file.

  It returns if the array is full.
  ***/
  bool writeHRM(int ppg, int deltatime){
    writePreamble(localHRMID, deltatime);
    writeBit(ppg>=0);
    if(ppg < 0){
      ppg = -(ppg+1);
    }
    int ppgLower = ppg & 127;
    
    writeNBits(ppgLower, 7);
    
    return hitLimit();
  }

  /***
  This function writes xyz-accelerometer data to the file.

  The values first need to be converted to int16 by multiplying the JS values with 8192.0.
  This reverses the division which was done by Espurino.

  It returns if the array is full.
  ***/
  bool writeAccelerometer(int xAccelerometer,int yAccelerometer,int zAccelerometer, int deltatime){

    writePreamble(localAccelID, deltatime);

    writeBit(xAccelerometer>=0);

    if(xAccelerometer<0){
      xAccelerometer = -(xAccelerometer+1);
    }

    unsigned char lowerByte = xAccelerometer & 255;
    xAccelerometer = xAccelerometer >> 8;
    unsigned char upperByte = xAccelerometer & 255;
	writeNBits(upperByte,7);
	writeByte(lowerByte);
    
    writeBit(yAccelerometer>=0);

    if(yAccelerometer<0){
      yAccelerometer = -(yAccelerometer+1);
    }

    lowerByte = yAccelerometer & 255;
    yAccelerometer = yAccelerometer >> 8;
    upperByte = yAccelerometer & 255;
    
	writeNBits(upperByte,7);
	writeByte(lowerByte);

    writeBit(zAccelerometer>=0);

    if(zAccelerometer<0){
      zAccelerometer = -(zAccelerometer+1);
    }

    lowerByte = zAccelerometer & 255;
    zAccelerometer = zAccelerometer >> 8;
    upperByte = zAccelerometer & 255;
    
	writeNBits(upperByte,7);
	writeByte(lowerByte);
	
    return hitLimit();
  }

  /***
  This function writes the magnetude data to the file.

  The value first need to be converted to int16 by multiplying the JS values with 8192.0.
  This reverses the division which was done by Espurino.

  It returns if the array is full.
  ***/
  bool writeMagnetude(int magnetude, int deltatime){

    writePreamble(localMagnetudeID, deltatime);

    unsigned char lowerByte = magnetude & 255;
    magnetude = magnetude >> 8;
    unsigned char upperByte = magnetude & 255;
	
	writeByte(upperByte);
	writeByte(lowerByte);

    return hitLimit();
  }

  /***
  This function writes the compass data to the file.

  The xyz-values of the compass are written by the compassData function.

  It returns if the array is full.
  ***/
  bool writeCompass(int xCompass, int yCompass, int zCompass, int deltatime){
    writePreamble(localCompassID, deltatime);


    writeBit(xCompass>=0);
    if(xCompass<0){
      xCompass = -(xCompass+1);
    }

    unsigned char lowerByte = xCompass & 255;
    xCompass = xCompass >> 8;
    unsigned char upperByte = xCompass & 15;


	writeNBits(upperByte,4);
	writeByte(lowerByte);
    
    writeBit(yCompass>=0);
    if(yCompass<0){
      yCompass = -(yCompass+1);
    }

    lowerByte = yCompass & 255;
    yCompass = yCompass >> 8;
    upperByte = yCompass & 15;

	writeNBits(upperByte,4);
	writeByte(lowerByte);

    writeBit(zCompass>=0);
    if(zCompass<0){
      zCompass = -(zCompass+1);
    }

    lowerByte = zCompass & 255;
    zCompass = zCompass >> 8;
    upperByte = zCompass & 15;

	writeNBits(upperByte,4);
	writeByte(lowerByte);

    writeDouble(heading, headingFloat32);

    return hitLimit();  
  }

  /***
  This function writes the xyz-Coordinates from the GPS data to the file.

  It returns if the array is full.
  ***/
  bool writeGPS(int deltatime){
    writePreamble(localGPSID,deltatime);

    writeDouble(xGPS,gpsFloat32);
    writeDouble(yGPS,gpsFloat32);
    writeDouble(zGPS,gpsFloat32);

    return hitLimit();
  }

  int getLimit(){
    return index;
  }
  int getByteWrite(){
    return byteWrite;
  }
  int getbyteIndex(){
    return byteIndex;
  }

  int getArrayIndex(int x){
    return array[x];
  }
`);

let storage = require("Storage");
let file = {
  name: "user.bin",
  offset: 0, // force a new file to be generated at first
};

// Add new data to a log file or switch log files
function saveData(ramData) {
  "ram"
  "jit"
  var l = ramData.length;
  if (file.offset == 0) {
    storage.write(file.name, ramData, 0, FILESIZE);
    file.offset = l;
  } else {
    // just append
    if (file.offset + l < FILESIZE) {
      storage.write(file.name, ramData, file.offset);
      file.offset += l;
    } else {
      let leftSpace = FILESIZE - file.offset;

      storage.write(file.name, ramData, leftSpace);
      file.offset += l + 100000;
    }
  }
}

function writeToFlash() {
  "ram"
  "jit"
  if (file.offset < FILESIZE) {
    saveData(writeBufferDataView.buffer);
  }

  historiographer.clear();
  if (file.offset >= FILESIZE) {
    print("dont");
    clearTimeout(drawTimeout);
    fullStorage();
    Bangle.buzz();
    Bangle.buzz();
    Bangle.buzz();
  }
}

let writeBuffer = new ArrayBuffer(1024);
let writeBufferDataView = new DataView(writeBuffer);
let writeBufferAddr = E.getAddressOf(writeBufferDataView.buffer, true);

let compassB = new ArrayBuffer(8);
let compassBDataView = new DataView(compassB);
let compassBAddr = E.getAddressOf(compassBDataView.buffer, true);

let latB = new ArrayBuffer(8);
let latBDataView = new DataView(latB);
let latBAddr = E.getAddressOf(latBDataView.buffer, true);

let longB = new ArrayBuffer(8);
let longBDataView = new DataView(longB);
let longBAddr = E.getAddressOf(longBDataView.buffer, true);

let altB = new ArrayBuffer(8);
let altBDataView = new DataView(altB);
let altBAddr = E.getAddressOf(altBDataView.buffer, true);

let supervisorname = "";
let subjectname = "";
let fastUpdateIntervall = true;

let recordAltitude = false;


let filenameSupervisor = false;
let filenameSubject = false;
let filenameDate = false;

let maxIndex = 1024;
let FILESIZE = 0;


function onHRM(hrm) {
  "ram"
  "jit"
  var timestamp = Math.round(Date.now());
  var deltaTime = timestamp - lastTimestamp;
  lastTimestamp = timestamp;

  var writeOut = historiographer.writeHRM(hrm.raw, deltaTime);
  if (writeOut == true) {
    writeToFlash();
  }
}

function onAccel(a) {
  "ram"
  "jit"
  var timestamp = Math.round(Date.now());
  var deltaTime = timestamp - lastTimestamp;
  lastTimestamp = timestamp;

  var writeOut = historiographer.writeAccelerometer(a.x * 8192.0, a.y * 8192.0, a.z * 8192.0, deltaTime);
  if (writeOut == true) {
    writeToFlash();
  }
}

function onMagnetude(a) {
  "ram"
  "jit"
  var timestamp = Math.round(Date.now());
  var deltaTime = timestamp - lastTimestamp;
  lastTimestamp = timestamp;

  var writeOut = historiographer.writeMagnetude(a.mag * 8192.0, deltaTime);
  if (writeOut == true) {
    writeToFlash();
  }
}

var compassSkip = 0;
var compassHeadingFloat32 = false;

function onCompass(c) {
  "ram"
  "jit"
  if (compassSkip == selectedCompass) {
    var timestamp = Math.round(Date.now());
    var deltaTime = timestamp - lastTimestamp;
    lastTimestamp = timestamp;

    compassHeadingFloat32 ? compassBDataView.setFloat32(0, c.heading, false) : compassBDataView.setFloat64(0, c.heading, false);
    var writeOut = historiographer.writeCompass(c.x, c.y, c.z, deltaTime);
    if (writeOut == true) {
      writeToFlash();
    }
    compassSkip = 0;
  } else {
    compassSkip++;
  }
}

var gpsSkips = 0;

function onGPS(gps) {
  "ram"
  "jit"
  if (!(isNaN(gps.lat) || isNaN(gps.lon) || isNaN(gps.alt))) {
    if (powersavingGPS) {
      //is valid
      var timestamp = Math.round(Date.now());
      var deltaTime = timestamp - lastTimestamp;
      lastTimestamp = timestamp;
      gpsFloat32 ? latBDataView.setFloat32(0, gps.lat, false) : latBDataView.setFloat64(0, gps.lat, false);
      gpsFloat32 ? longBDataView.setFloat32(0, gps.lon, false) : longBDataView.setFloat64(0, gps.lon, false);
      gpsFloat32 ? altBDataView.setFloat32(0, gps.alt, false) : altBDataView.setFloat64(0, gps.alt, false);

      var writeOut = historiographer.writeGPS(deltaTime);
      if (writeOut == true) {
        writeToFlash();
      }
      // turn off
      Bangle.setGPSPower(0);
    } else {
      if (gpsSkips == selectedGPSspeed) {
        var timestamp = Math.round(Date.now());
        var deltaTime = timestamp - lastTimestamp;
        lastTimestamp = timestamp;

        gpsFloat32 ? latBDataView.setFloat32(0, gps.lat, false) : latBDataView.setFloat64(0, gps.lat, false);
        gpsFloat32 ? longBDataView.setFloat32(0, gps.lon, false) : longBDataView.setFloat64(0, gps.lon, false);
        gpsFloat32 ? altBDataView.setFloat32(0, gps.alt, false) : altBDataView.setFloat64(0, gps.alt, false);
        var writeOut = historiographer.writeGPS(deltaTime);
        if (writeOut == true) {
          writeToFlash();
        }
        gpsSkips = 0;
      } else {
        gpsSkips++;
      }
    }
  }
}


function gpsTurnON() {
  Bangle.setGPSPower(1);
}

function writeNames() {
  let lengthName = supervisorname.length;
  arrayIndex = historiographer.writeByte(lengthName);

  let charToWrite = 0;
  for (let i = 0; i < lengthName; i++) {
    charToWrite = supervisorname[i].charCodeAt(0);
    arrayIndex = historiographer.writeByte(charToWrite);
    if (historiographer.hitLimit() == true) {
      writeToFlash();
    }
  }
  subjectname = subjectname.toString();
  lengthName = subjectname.length;
  arrayIndex = historiographer.writeByte(lengthName);
  if (historiographer.hitLimit() == true) {
    writeToFlash();
  }

  for (let i = 0; i < lengthName; i++) {
    charToWrite = subjectname[i].charCodeAt(0);
    arrayIndex = historiographer.writeByte(charToWrite);
    if (historiographer.hitLimit() == true) {
      writeToFlash();
    }
  }
}
var accelBypass;
var accelfilter;
var accelOutputDataRate;
var accelSamples;
var accelResMode;
var accelRange;

function writeConfiguration() {

  require("Storage").erase("user.bin");
  require("Storage").compact(true);

  //writeBuffer = new ArrayBuffer(maxIndex);
  //writeBufferDataView = new DataView(writeBuffer);
  //writeBufferAddr = E.getAddressOf(writeBufferDataView.buffer);

  historiographer.initArray(writeBufferAddr, maxIndex);

  historiographer.writeByte(1)

  writeNames();
  historiographer.writeBit(0);
  historiographer.writeIDsToArray();

  historiographer.namingOutputFile(filenameSupervisor, filenameSubject, filenameDate);
  
  //create folder for supervisor
  historiographer.writeBit(1);
  //create folder for subject
  historiographer.writeBit(1);
  //create folder for date
  historiographer.writeBit(0);

  if (selectedHRM != 0) {
    Bangle.setHRMPower(1);
  }

  if (selectedMagnitude != 0 || selectedAccelerometer != 0) {
    let i2c = I2C();
    i2c.setup({
      scl: D14,
      sda: D15,
      bitrate: 100000
    });
    i2c.writeTo(0x1E, [0x18, 0b01110100]);
    var odcntrl = 128 * accelBypass + 64 * accelfilter + accelOutputDataRate;
    i2c.writeTo(0x1E, [0x1B, odcntrl]);
    var locntl = accelSamples << 4;
    i2c.writeTo(0x1E, [0x35, locntl]);
    var cntl1 = 64 * accelResMode + 32 + 8 * accelRange;
    i2c.writeTo(0x1E, [0x18, cntl1]);
    cntl1 = cntl1 + 128;
    i2c.writeTo(0x1E, [0x18, cntl1])
  }

  if (selectedCompass != "Off") {
    Bangle.setCompassPower(1);
  }
  if (selectedGPSspeed != "Off") {
    Bangle.setGPSPower(1);
  }

  //deleteVariables();
  //E.defrag();
  //draw();

  Bangle.buzz();
  Bangle.buzz();
  LED1.set()
}

function start() {
  E.showMenu(submenuClock);
  drawFaceScreen();
  
  var time = Math.round(Date.now());
  lastTimestamp = time;
  var date = Date(time);
  historiographer.writeDate(date.getFullYear(), date.getMonth(), date.getDate());
  var writeOut = historiographer.writeTime(date.getHours(), date.getMinutes());

  if (selectedHRM != 0) {
    Bangle.on('HRM-raw', onHRM);
  }
  if (selectedAccelerometer != 0) {
    Bangle.on('accel', onAccel);
  }
  if (selectedMagnitude != 0) {
    Bangle.on('accel', onMagnetude);
  }
  if (selectedCompass != "Off") {
    Bangle.on('mag', onCompass);
  }
  if (selectedGPSspeed != "Off") {
    Bangle.on('GPS', onGPS);
  }

  if (writeOut == true) {
    writeToFlash();
  }
}

function bleStart(data) {
  Bluetooth.removeListener('data', bleStart);
  setTime(data);
  LED2.set()
  start();
  Bangle.buzz();
}

var lastTimestamp = 0;

var selectedHRM = 0;
var selectedAccelerometer = false;
var selectedMagnitude = false;
var selectedCompass = 0;
var selectedGPSspeed = 0;
var selectedProfile = false;

var master = false;

var debug = false;

var profiles = require("Storage").readJSON("availableConfigs.json", true).configs;
profiles.unshift("Custom");

var currentProfile = profiles[0];

function loadProfile(id) {
  if (id != 0) {
    selectedProfile = true;
    currentProfile = profiles[id];

    var setting = require("Storage").readJSON(currentProfile + ".json", true);
    supervisorname = setting.supervisorname;
    subjectname = Number(setting.subjectname)

    FILESIZE = setting.fileSize * 1024;
    //maxIndex = setting.ramSize;

    selectedHRM = setting.hrmSpeedB1;
    if (setting.hrmSpeedB1 != "Off") {
      let options = Bangle.getOptions();
      options.hrmPollInterval = setting.hrmSpeedB1;
      Bangle.setOptions(options);
      Bangle.setHRMPower(true, appID);
      historiographer.setHRM(true, setting.hrmReduction, setting.hrmFiller);
    }
    selectedAccelerometer = setting.accelerometer;

    if (setting.accelerometer != 0) {
      historiographer.setAccelerometer(setting.accelerometer, setting.accelRange);
    }

    selectedMagnitude = setting.magnitude;

    if (setting.magnetude != 0) {
      historiographer.setMagnetude(setting.magnetude, setting.accelRange);
    }

    accelBypass = setting.accelBypass;
    accelfilter = setting.accelfilter;
    accelOutputDataRate = setting.accelOutputDataRate;
    accelSamples = setting.accelSamples;
    accelResMode = setting.accelResMode;
    accelRange = setting.accelRange;

    selectedCompass = setting.compassB1;
    if (setting.compassB1 != "Off") {
      Bangle.setCompassPower(1, appID);
      compassHeadingFloat32 = setting.compassHeadingFloat32;
      historiographer.setCompass(true, setting.compassHeadingFloat32, compassBAddr);
    }

    selectedGPSspeed = setting.gpsSpeedB1;
    if (setting.gpsSpeedB1 != "Off") {
      Bangle.setGPSPower(1);
      gpsFloat32 = setting.gpsFloat32
      historiographer.setGPS(true, setting.gpsFloat32);
      historiographer.setGPSaddresses(latBAddr, longBAddr, altBAddr);
      if (setting.gpsEnergysaving == true) {
        gpsTurnOnIntervallFunction = setInterval(gpsTurnON, setting.gPSspeedSeconds * 1000);
      }
    }

    if (setting.fastUpdateIntervall == true) {
      Bangle.setPollInterval(10);
    }

    master = setting.master;

    debug = setting.debug;

    showClock = setting.showClock;
    showDate = setting.showDate;
    updateDate = setting.updateDate;
  } else {
    currentProfile = profiles[0];
  }
}

if(profiles.length > 1)
  loadProfile(1);

function deleteVariables() {
  supervisorname = null;
  subjectname = null;
  filenameSupervisor = null;
  filenameSubject = null;
  filenameDate = null;
  fillerOptions = null;

  debug = null;
  profiles = null;
  currentProfile = null;
}
var submenuClock;
var submenuStart;

var submenuStartTitle = "Ready for "

submenuStart = {
  "": {
    "title": "Ready for " + subjectname
  },
}


// First menu
var mainmenu = {
  "": {
    "title": "Main Menu"
  },
  "< Back": function() {
    load();
  },
  "ID:":{
    value : subjectname,
    min: 0,
    max: 10000,
    step: 1,
    onchange : v => { subjectname = v; }
  },
  "Start": function() {
    if (selectedProfile) {
      submenuStartTitle += subjectname;
      submenuStart = {
        "": {
          "title": submenuStartTitle
        },
        "Bangle.js" : {value : NRF.getAddress().substring(12)},
        "Ready": function(){
          E.setConsole(null);
          Bluetooth.on('data', bleStart);
          E.showMenu(submenuClock);
          LED1.set();},
      }
      writeConfiguration();
      E.showMenu(submenuStart);
      //E.showMenu(submenuStart);
      //writeConfiguration();
      //E.setConsole(null);
      //Bluetooth.on('data', bleStart);
      //E.showMenu(submenuClock);
      //LED1.set()
      
    }
  },
  "Profile: ": {
    value: 1,
    min: 0,
    max: profiles.length - 1,
    format: v => profiles[v],
    onchange: v => {
      loadProfile(v);
    }
  },
  "Exit": function() {
    load();
  }, // remove the menu
};





var fullStorage = function() {
  g.clear(true);

  g.setFont("Vector", 15);
  g.drawString("Please return to", 5, 30, true);
  g.drawString("Supervisor", 5, 50, true);
  g.drawString("Storage is full", 5, 80, true);

  g.drawRect(40, 130, 130, 170);
  g.setFont("Vector", 20);
  g.drawString("OK", 70, 140);

  noMoreStorage = true;
};


var m = E.showMenu(mainmenu);

E.on('kill', function() {
  //writeEnd
  historiographer.writePreamble(255, 0);
  historiographer.writePreamble(255, 0);
  writeToFlash();

  //restore accel to old settings
  let i2c = I2C();
  i2c.setup({
    scl: D14,
    sda: D15,
    bitrate: 100000
  });
  i2c.writeTo(0x1E, [0x18, 0b01110100]);
  i2c.writeTo(0x1E, [0x35, 32]);
  i2c.writeTo(0x1E, [0x1B, 0]);
  i2c.writeTo(0x1E, [0x3E, 0]);
  i2c.writeTo(0x1E, [0x18, 0b10101100])

});
