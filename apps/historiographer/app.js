//Anton Clock
//https://github.com/espruino/BangleApps/tree/master/apps/antonclk
// Clock with large digits using the "Anton" bold font
Graphics.prototype.setFontAnton = function(scale) {
// Actual height 69 (68 - 0)
g.setFontCustom(atob("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADgAAAAAAAAAAA/gAAAAAAAAAAP/gAAAAAAAAAH//gAAAAAAAAB///gAAAAAAAAf///gAAAAAAAP////gAAAAAAD/////gAAAAAA//////gAAAAAP//////gAAAAH///////gAAAB////////gAAAf////////gAAP/////////gAD//////////AA//////////gAA/////////4AAA////////+AAAA////////gAAAA///////wAAAAA//////8AAAAAA//////AAAAAAA/////gAAAAAAA////4AAAAAAAA///+AAAAAAAAA///gAAAAAAAAA//wAAAAAAAAAA/8AAAAAAAAAAA/AAAAAAAAAAAAgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD//////AAAAAB///////8AAAAH////////AAAAf////////wAAA/////////4AAB/////////8AAD/////////+AAH//////////AAP//////////gAP//////////gAP//////////gAf//////////wAf//////////wAf//////////wAf//////////wA//8AAAAAB//4A//wAAAAAAf/4A//gAAAAAAP/4A//gAAAAAAP/4A//gAAAAAAP/4A//wAAAAAAf/4A///////////4Af//////////wAf//////////wAf//////////wAf//////////wAP//////////gAP//////////gAH//////////AAH//////////AAD/////////+AAB/////////8AAA/////////4AAAP////////gAAAD///////+AAAAAf//////4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP/gAAAAAAAAAAP/gAAAAAAAAAAf/gAAAAAAAAAAf/gAAAAAAAAAAf/AAAAAAAAAAA//AAAAAAAAAAA/+AAAAAAAAAAB/8AAAAAAAAAAD//////////gAH//////////gAP//////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH/4AAAAB/gAAD//4AAAAf/gAAP//4AAAB//gAA///4AAAH//gAB///4AAAf//gAD///4AAA///gAH///4AAD///gAP///4AAH///gAP///4AAP///gAf///4AAf///gAf///4AB////gAf///4AD////gA////4AH////gA////4Af////gA////4A/////gA//wAAB/////gA//gAAH/////gA//gAAP/////gA//gAA///8//gA//gAD///w//gA//wA////g//gA////////A//gA///////8A//gA///////4A//gAf//////wA//gAf//////gA//gAf/////+AA//gAP/////8AA//gAP/////4AA//gAH/////gAA//gAD/////AAA//gAB////8AAA//gAA////wAAA//gAAP///AAAA//gAAD//8AAAA//gAAAP+AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB/+AAAAAD/wAAB//8AAAAP/wAAB///AAAA//wAAB///wAAB//wAAB///4AAD//wAAB///8AAH//wAAB///+AAP//wAAB///+AAP//wAAB////AAf//wAAB////AAf//wAAB////gAf//wAAB////gA///wAAB////gA///wAAB////gA///w//AAf//wA//4A//AAA//wA//gA//AAAf/wA//gB//gAAf/wA//gB//gAAf/wA//gD//wAA//wA//wH//8AB//wA///////////gA///////////gA///////////gA///////////gAf//////////AAf//////////AAP//////////AAP/////////+AAH/////////8AAH///+/////4AAD///+f////wAAA///8P////gAAAf//4H///+AAAAH//gB///wAAAAAP4AAH/8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD/wAAAAAAAAAA//wAAAAAAAAAP//wAAAAAAAAB///wAAAAAAAAf///wAAAAAAAH////wAAAAAAA/////wAAAAAAP/////wAAAAAB//////wAAAAAf//////wAAAAH///////wAAAA////////wAAAP////////wAAA///////H/wAAA//////wH/wAAA/////8AH/wAAA/////AAH/wAAA////gAAH/wAAA///4AAAH/wAAA//+AAAAH/wAAA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gA///////////gAAAAAAAAH/4AAAAAAAAAAH/wAAAAAAAAAAH/wAAAAAAAAAAH/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB//8AAA/////+B///AAA/////+B///wAA/////+B///4AA/////+B///8AA/////+B///8AA/////+B///+AA/////+B////AA/////+B////AA/////+B////AA/////+B////gA/////+B////gA/////+B////gA/////+A////gA//gP/gAAB//wA//gf/AAAA//wA//gf/AAAAf/wA//g//AAAAf/wA//g//AAAA//wA//g//gAAA//wA//g//+AAP//wA//g////////gA//g////////gA//g////////gA//g////////gA//g////////AA//gf///////AA//gf//////+AA//gP//////+AA//gH//////8AA//gD//////4AA//gB//////wAA//gA//////AAAAAAAH////8AAAAAAAA////AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD//////gAAAAB///////+AAAAH////////gAAAf////////4AAB/////////8AAD/////////+AAH//////////AAH//////////gAP//////////gAP//////////gAf//////////wAf//////////wAf//////////wAf//////////wAf//////////4A//wAD/4AAf/4A//gAH/wAAP/4A//gAH/wAAP/4A//gAP/wAAP/4A//gAP/4AAf/4A//wAP/+AD//4A///wP//////4Af//4P//////wAf//4P//////wAf//4P//////wAf//4P//////wAP//4P//////gAP//4H//////gAH//4H//////AAH//4D/////+AAD//4D/////8AAB//4B/////4AAA//4A/////wAAAP/4AP////AAAAB/4AD///4AAAAAAAAAH/8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA//AAAAAAAAAAA//gAAAAAAAAAA//gAAAAAAAAAA//gAAAAAAADgA//gAAAAAAP/gA//gAAAAAH//gA//gAAAAB///gA//gAAAAP///gA//gAAAD////gA//gAAAf////gA//gAAB/////gA//gAAP/////gA//gAB//////gA//gAH//////gA//gA///////gA//gD///////gA//gf///////gA//h////////gA//n////////gA//////////gAA/////////AAAA////////wAAAA///////4AAAAA///////AAAAAA//////4AAAAAA//////AAAAAAA/////4AAAAAAA/////AAAAAAAA////8AAAAAAAA////gAAAAAAAA///+AAAAAAAAA///4AAAAAAAAA///AAAAAAAAAA//4AAAAAAAAAA/+AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD//gB///wAAAAP//4H///+AAAA///8P////gAAB///+f////4AAD///+/////8AAH/////////+AAH//////////AAP//////////gAP//////////gAf//////////gAf//////////wAf//////////wAf//////////wA///////////wA//4D//wAB//4A//wB//gAA//4A//gA//gAAf/4A//gA//AAAf/4A//gA//gAAf/4A//wB//gAA//4A///P//8AH//4Af//////////wAf//////////wAf//////////wAf//////////wAf//////////gAP//////////gAP//////////AAH//////////AAD/////////+AAD///+/////8AAB///8f////wAAAf//4P////AAAAH//wD///8AAAAA/+AAf//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH//gAAAAAAAAB///+AA/+AAAAP////gA//wAAAf////wA//4AAB/////4A//8AAD/////8A//+AAD/////+A///AAH/////+A///AAP//////A///gAP//////A///gAf//////A///wAf//////A///wAf//////A///wAf//////A///wA///////AB//4A//4AD//AAP/4A//gAB//AAP/4A//gAA//AAP/4A//gAA/+AAP/4A//gAB/8AAP/4A//wAB/8AAf/4Af//////////wAf//////////wAf//////////wAf//////////wAf//////////wAP//////////gAP//////////gAH//////////AAH/////////+AAD/////////8AAB/////////4AAAf////////wAAAP////////AAAAB///////4AAAAAD/////wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAf/AAB/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAA//AAD/8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=="), 46, atob("EiAnGicnJycnJycnEw=="), 78 + (scale << 8) + (1 << 16));
};

// must be inside our own scope here so that when we are unloaded everything disappears
// we also define functions using 'let fn = function() {..}' for the same reason. function decls are global
let drawTimeout;

// Actually draw the watch face
let draw = function() {
  console.log("draw called");
  var x = g.getWidth() / 2;
  var y = g.getHeight() / 2;
  g.reset().clearRect(Bangle.appRect); // clear whole background (w/o widgets)
  var date = new Date();
  var timeStr = require("locale").time(date, 1); // Hour and minute
  g.setFontAlign(0, 0).setFont("Anton").drawString(timeStr, x, y);
  // Show date and day of week
  var dateStr = require("locale").date(date, 0).toUpperCase()+"\n"+
                require("locale").dow(date, 0).toUpperCase();
  g.setFontAlign(0, 0).setFont("6x8", 2).drawString(dateStr, x, y+48);

  // queue next draw
  if (drawTimeout) clearTimeout(drawTimeout);
  drawTimeout = setTimeout(function() {
    if(drawTimeout != null){
      drawTimeout = undefined;
      draw();
    }
  }, 60000 - (Date.now() % 60000));
};

// Load widgets
Bangle.loadWidgets();
setTimeout(Bangle.drawWidgets,0);

function hrmTurnoff(soft){
  if(soft)
  {
    Bangle.setHRMPower(false, appID);
    hrmActive = false;
  }
  else
  {    
    Bangle.setHRMPower(false);
  }
}

function accelTurnoff(soft)
{
  powerAccelerometer = false;
}

function magnetudeTurnoff(soft)
{
  powerMagnetude = false;
}

function compassTurnoff(soft)
{
  if(soft)
  {
    Bangle.setCompassPower(false, appID);
    compassActive = false;
  }
  else
  {    
    Bangle.setCompassPower(false);
  }
}

function gpsTurnoff(soft)
{
  if(soft)
  {
    Bangle.setGPSPower(false, appID);
    gpsActive = false;
  }
  else
  {    
    Bangle.setGPSPower(false);
  }
}

function barometerTurnoff(soft)
{
  if(soft)
  {
    Bangle.setBarometerPower(false, appID);
    barometerActive = false;
  }
  else
  {    
    Bangle.setBarometerPower(false);
  }
}

let powerTurnoffBattery = [false,false,false,false,false,false];
let powerTurnoffStorage = [false,false,false,false,false,false];
let powersavingGPS = false;
let gpsTurnOnIntervallFunction;

let powerTurnoffFunctions = [hrmTurnoff,barometerTurnoff,accelTurnoff,magnetudeTurnoff,compassTurnoff,gpsTurnoff];

let batteryNotifiyAction = false;
let storageNotifiyAction = false;
let batteryNotifiyPercent = 0;
let storageNotifiy = 0;

let batterySaveAction = false;
let storageSaveAction = false;
let batterySavePercent = 0;
let storageSave = 0;

let showingWarning = false;
let noMoreStorage = false;

let appID = "historio";

let historiographer= E.compiledC(`
  // void initArray(int, int)
  // void clear()
  // void writeIDs()
  // void setHRM(bool)
  // void setBarometer(bool)
  // void setAccelerometer(bool)
  // void setMagnetude(bool)
  // void setCompass(bool)
  // void setGPS(bool)
  // bool writeIDsToArray()
  // bool writeOptions1(bool, bool, bool)
  // bool writeOptions2(bool, bool, bool)
  // bool writeDate(int, int, int)
  // bool writeTime(int, int)
  // bool writeBarometer(int, int, int, int)
  // bool writeHRM(int, int)
  // bool writeAccelerometer(int,int,int,int)
  // bool writeMagnetude(int, int)
  // void compassData(int, int, int)
  // bool writeCompass(int, int)
  // bool writeGPS(int, int, int, int)
  // void writeToArray()
  // void writeBit(bool)
  // void writeNBits(int,int)
  // void writeByte(int)
  // void writePreamble(int, int)
  // void writeDouble(int)
  // bool hitLimit()
  // int getIndex()
  // int writeEndID(int)


  /***
  Local variables
  ***/
  //writeBuffer and the index
  unsigned char byteWrite = 0;
  unsigned char byteIndex = 0;

  //save Compass data, because Espurino only allows 4 arguments
  int xCompass = 0;
  int yCompass = 0;
  int zCompass = 0;

  //Array and information
  unsigned char* array;
  int index = 0;
  int maxIndex = 0;

  unsigned char overflowArray[30];
  int indexOverflow = 0;

  //Local ID encoding 
  char localIDLength = 0;
  char localHRMID = 0;
  char localBarometerID = 0;
  char localAccelID = 0;
  char localMagnetudeID = 0;
  char localCompassID = 0;
  char localGPSID = 0;

  //is sensor used?
  bool localHRMUse = 0;
  bool localBarometerUse = 0;
  bool localAccelUse = 0;
  bool localMagnetudeUse = 0;
  bool localCompassUse = 0;
  bool localGPSUse = 0;

  //options if the height from barometer should be saved or calculated later
  bool saveHeight = false;

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
  void writeDouble(unsigned char* doubleVal){

    for(int i = 0; i < 8; i++){
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
  void setBarometer(bool state){
    localBarometerUse = state;
  }
  void setAccelerometer(bool state){
    localAccelUse = state;
  }
  void setMagnetude(bool state){
    localMagnetudeUse = state;
  }
  void setCompass(bool state){
    localCompassUse = state;
  }
  void setGPS(bool state){
    localGPSUse = state;
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
    if(localBarometerUse == 1){
      localBarometerID = id;
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
    if(localBarometerUse != 0){
      writeNBits(localBarometerID, localIDLength);
    writeByte(2);
    }
    if(localAccelUse != 0){
      writeNBits(localAccelID, localIDLength);
    writeByte(3);
    }
    if(localMagnetudeUse != 0){
      writeNBits(localMagnetudeID, localIDLength);
    writeByte(4);
    }
    if(localCompassUse != 0){
      writeNBits(localCompassID, localIDLength);
    writeByte(5);
    }
    if(localGPSUse != 0){
      writeNBits(localGPSID, localIDLength);
    writeByte(6);
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
  It indicates if the height should be saved or calculated later.
  Select if the decoder should use JSMath or more accurate version.
  It determents the output format of the decoder (XML or CSV). 

  It returns if the array is full.
  ***/
  bool writeOptions1(bool saveHeight_,bool jsMath, bool saveXML){
    saveHeight = saveHeight_;
    writeBit(saveHeight);
  writeBit(jsMath);
    writeBit(saveXML);

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
  bool writeOptions2(bool filenameSupervisor,bool filenameSubject, bool filenameDate){
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
  This function writes the barometer values to the file.

  if saveHeight was turned on the height will be saved as well.

  It returns if the array is full.
  ***/
  bool writeBarometer(unsigned char* temperature, unsigned char* pressure, unsigned char* height, int deltatime){

    writePreamble(localBarometerID, deltatime);

    // finde exponent heraus

    writeDouble(temperature);
    writeDouble(pressure);

    if(saveHeight){
      writeDouble(height);
    }


    return hitLimit();
  }  

  /***
  This function writes the ppg value to the file.

  It returns if the array is full.
  ***/
  bool writeHRM(int ppg, int deltatime){
    unsigned char ppgLower = ppg & 255;
    ppg = ppg >> 8;
    unsigned char ppgUpper = ppg & 15;

    writePreamble(localHRMID, deltatime);
    writeNBits(ppgUpper, 4);
    writeByte(ppgLower);

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
      xAccelerometer = -xAccelerometer;
    }

    unsigned char lowerByte = xAccelerometer & 255;
    xAccelerometer = xAccelerometer >> 8;
    unsigned char upperByte = xAccelerometer & 255;
    writeByte(upperByte);
    writeByte(lowerByte);

    writeBit(yAccelerometer>=0);

    if(yAccelerometer<0){
      yAccelerometer = -yAccelerometer;
    }

    lowerByte = yAccelerometer & 255;
    yAccelerometer = yAccelerometer >> 8;
    upperByte = yAccelerometer & 255;
    writeByte(upperByte);
    writeByte(lowerByte);

    writeBit(zAccelerometer>=0);

    if(zAccelerometer<0){
      zAccelerometer = -zAccelerometer;
    }

    lowerByte = zAccelerometer & 255;
    zAccelerometer = zAccelerometer >> 8;
    upperByte = zAccelerometer & 255;
    writeByte(upperByte);
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

    writeBit(magnetude>=0);

    if(magnetude<0){
      magnetude = -magnetude;
    }

    unsigned char lowerByte = magnetude & 255;
    magnetude = magnetude >> 8;
    unsigned char upperByte = magnetude & 255;
    writeByte(upperByte);
    writeByte(lowerByte);

    return hitLimit();
  }

  /***
  This function writes the xyz-compass data to local variables.

  This is done because only 4 arguments are allowd by the inline C compiler.
  Making 2 function calles instead of writing the xyz-values to predetermend JS-Array saves 1 ms.
  ***/
  void compassData(int x,int y,int z){
    xCompass = x;
    yCompass = y;
    zCompass = z;
  }

  /***
  This function writes the compass data to the file.

  The xyz-values of the compass are written by the compassData function.

  It returns if the array is full.
  ***/
  bool writeCompass(unsigned char* heading, int deltatime){
    writePreamble(localCompassID, deltatime);


    writeBit(xCompass>=0);
    if(xCompass<0){
      xCompass = -xCompass;
    }

    unsigned char lowerByte = xCompass & 255;
    xCompass = xCompass >> 8;
    unsigned char upperByte = xCompass & 15;
    writeNBits(upperByte, 4);
    writeByte(lowerByte);

    writeBit(yCompass>=0);
    if(yCompass<0){
      yCompass = -yCompass;
    }

    lowerByte = yCompass & 255;
    yCompass = yCompass >> 8;
    upperByte = yCompass & 15;
    writeNBits(upperByte, 4);
    writeByte(lowerByte);

    writeBit(zCompass>=0);
    if(zCompass<0){
      zCompass = -zCompass;
    }

    lowerByte = zCompass & 255;
    zCompass = zCompass >> 8;
    upperByte = zCompass & 15;
    writeNBits(upperByte, 4);
    writeByte(lowerByte);

    writeDouble(heading);

    return hitLimit();  
  }

  /***
  This function writes the xyz-Coordinates from the GPS data to the file.

  It returns if the array is full.
  ***/
  bool writeGPS(unsigned char* xGPS,unsigned char* yGPS,unsigned char* zGPS,int deltatime){
    writePreamble(localGPSID,deltatime);

    writeDouble(xGPS);
    writeDouble(yGPS);
    writeDouble(zGPS);

    return hitLimit();
  }

  /***
  This function returns the current index of the array.
  ***/
  int getIndex(){
    return index;
  }

  int writeEndID(int deltatime){
    writePreamble(localAccelID, deltatime);
    writeByte(255);
    
    if(indexOverflow == 0){
      return false;
    }
    else{
      return true;
    }
  }
`);

let storage = require("Storage");
let file = {
  name : "user.bin",
  offset : 0, // force a new file to be generated at first
};

// Add new data to a log file or switch log files
function saveData(ramData) {
  var l = ramData.length;
  if(file.offset == 0){
    storage.write(file.name,ramData,0,FILESIZE);
    file.offset = l;
    print("create File");
  }
  else{
  // just append
    if(file.offset+l < FILESIZE){
      storage.write(file.name,ramData,file.offset);
      file.offset += l;
    }
    else{
      let leftSpace = FILESIZE - file.offset;
      
      let tempBuffer = new ArrayBuffer(leftSpace);
      let tempBufferDataView = new DataView(tempBuffer);
      
      for (let i = 0; i < leftSpace; i++) {
        let valueToWrite = writeBufferDataView.getInt8(i);
        tempBufferDataView.setInt8(i,valueToWrite);
      }
      
      storage.write(file.name,tempBufferDataView.buffer,file.offset);
      file.offset += l + 100000;
    }
  }
}

function writeToFlash(){
  if(file.offset < FILESIZE){
    saveData(writeBufferDataView.buffer);
  }
  
  if(file.offset >=  storageNotifiy && storageNotifiyAction)
  {
  if(showingWarning == false)
  {
    clearTimeout(drawTimeout);
    warnings();
    Bangle.buzz();
    storageNotifiyAction = false;
  }
  }
  
  if(file.offset >=  storageSave && storageSaveAction)
  {
    if(showingWarning == false)
    {
      clearTimeout(drawTimeout);
      warnings();
      Bangle.buzz();
      storageSaveAction = false;
      for (let i = 0; i < powerTurnoffStorage.length; i++) {
        if(powerTurnoffStorage[i])
          powerTurnoffFunctions[i](true);
      }
    }
  }

  historiographer.clear();
  if(file.offset >= FILESIZE){
    clearTimeout(drawTimeout);
    fullStorage();
    Bangle.buzz();
    Bangle.buzz();
    Bangle.buzz();
  }
}

let writeBuffer = new ArrayBuffer(0);
let writeBufferDataView = new DataView(writeBuffer);
let writeBufferAddr = E.getAddressOf(writeBufferDataView.buffer,true);

let tempB = new ArrayBuffer(8);
let tempBDataView = new DataView(tempB);
let tempBAddr = E.getAddressOf(tempBDataView.buffer,true);

let pressB = new ArrayBuffer(8);
let pressBDataView = new DataView(pressB);
let pressBAddr = E.getAddressOf(pressBDataView.buffer,true);

let pressAltB = new ArrayBuffer(8);
let pressAltBDataView = new DataView(pressAltB);
let pressAltBAddr = E.getAddressOf(pressAltBDataView.buffer,true);

let compassB = new ArrayBuffer(8);
let compassBDataView = new DataView(compassB);
let compassBAddr = E.getAddressOf(compassBDataView.buffer,true);

let latB = new ArrayBuffer(8);
let latBDataView = new DataView(latB);
let latBAddr = E.getAddressOf(latBDataView.buffer,true);

let longB = new ArrayBuffer(8);
let longBDataView = new DataView(longB);
let longBAddr = E.getAddressOf(longBDataView.buffer,true);

let altB = new ArrayBuffer(8);
let altBDataView = new DataView(altB);
let altBAddr = E.getAddressOf(altBDataView.buffer,true);

var supervisorname = "";
var subjectname = "";
var fastUpdateIntervall = false;

let recordAltitude = false;
let jsMath = false;
let outputXML = false;

let filenameSupervisor = false;
let filenameSubject = false;
let filenameDate = false;

let maxIndex = 768;
let FILESIZE = 0;

let started = false;

let powerAccelerometer = false;
let powerMagnetude = false;
let gpsActive = false;
let barometerActive = false;
let hrmActive = false;
let compassActive = false;

function writeNames(){
  let lengthName = supervisorname.length;
  arrayIndex = historiographer.writeByte(lengthName);

  let charToWrite = 0;
  for(let i=0; i<lengthName;i ++) {
    charToWrite = supervisorname[i].charCodeAt(0);
    arrayIndex = historiographer.writeByte(charToWrite);
  if(historiographer.hitLimit() == true){
      writeToFlash();
    }
  }

  lengthName = subjectname.length;
  arrayIndex = historiographer.writeByte(lengthName);
  if(historiographer.hitLimit() == true){
      writeToFlash();
    }

  for(let i=0; i<lengthName;i ++) {
    charToWrite = subjectname[i].charCodeAt(0);
    arrayIndex = historiographer.writeByte(charToWrite);
  if(historiographer.hitLimit() == true){
      writeToFlash();
    }
  }
}

var gpsSkips = 0;
function onGPS(gps){
  if(started && gpsActive){
    if(powersavingGPS){
      if(!(isNaN(gps.lat) || isNaN(gps.lon) || isNaN(gps.alt))){
        //is valid
        var timestamp = Math.round(Date.now());
        var deltaTime = timestamp - lastTimestamp;
        lastTimestamp = timestamp;  

        latBDataView.setFloat64(0,gps.lat,true);
        longBDataView.setFloat64(0,gps.lon,true);
        altBDataView.setFloat64(0,gps.alt,true);

        var writeOut = historiographer.writeGPS(latBAddr,longBAddr,altBAddr,deltaTime);
        if(writeOut == true){
          writeToFlash();
        }
        // turn off
        Bangle.setGPSPower(0);
      }
    }
    else{
      if(gpsSkips == GPSspeed[selectedGPSspeed]){
        var timestamp = Math.round(Date.now());
        var deltaTime = timestamp - lastTimestamp;
        lastTimestamp = timestamp;  

        latBDataView.setFloat64(0,gps.lat,true);
        longBDataView.setFloat64(0,gps.lon,true);
        altBDataView.setFloat64(0,gps.alt,true);

        var writeOut = historiographer.writeGPS(latBAddr,longBAddr,altBAddr,deltaTime);
        if(writeOut == true){
          writeToFlash();
        }
        gpsSkips = 0;
      }
      else{
        gpsSkips++;
      }
    }
  }
}

function gpsTurnON(){
  Bangle.setGPSPower(1);
}

var barometerSkip = 0;

function onBarometer(baro){
  if(started && barometerActive){
    if(barometerSkip == barometerSkips[selectedBarometer]){
      var timestamp = Math.round(Date.now());
      var deltaTime = timestamp - lastTimestamp;
      lastTimestamp = timestamp;  

      tempBDataView.setFloat64(0,baro.temperature,true);
      pressBDataView.setFloat64(0,baro.pressure,true);
      if(recordAltitude){
        pressAltBDataView.setFloat64(0,baro.altitude,true);
      }
      var writeOut = historiographer.writeBarometer(tempBAddr,pressBAddr,pressAltBAddr,deltaTime);
      if(writeOut == true){
        writeToFlash();
      }
      barometerSkip = 0;
    }
    else{
      barometerSkip++;
    }    
  }
}

function onHRM(h){
  if(started && hrmActive){
    var timestamp = Math.round(Date.now());
    var deltaTime = timestamp - lastTimestamp;
    lastTimestamp = timestamp;

    var ppg = h.vcPPG;
    var writeOut = historiographer.writeHRM(ppg,deltaTime);
    if(writeOut == true){
      writeToFlash();
    }
  }
}

var compassSkip = 0;
function onCompass(c){
  if(started && compassActive){
    if(compassSkip == compassSkips[selectedCompass]){
      var timestamp = Math.round(Date.now());
      var deltaTime = timestamp - lastTimestamp;
      lastTimestamp = timestamp;

      var x = c.x;
      var y = c.y;
      var z = c.z;

      var heading = c.heading;
      historiographer.compassData(x,y,z);

      compassBDataView.setFloat64(0,heading,true);

      var writeOut = historiographer.writeCompass(compassBAddr,deltaTime);
      if(writeOut == true){
        writeToFlash();
      }
      compassSkip = 0;
    }
    else
    {
      compassSkip++;
    }
  }
}

var accelerometerSkip = 0;
function onAccel(a){
  if(started){
    if(accelerometerSkip == accelerometerSkips[selectedAccelerometer]){
      var timestamp = Math.round(Date.now());
      var deltaTime = timestamp - lastTimestamp;
      lastTimestamp = timestamp;
      var x = a.x * 8192.0;
      var y = a.y * 8192.0;
      var z = a.z * 8192.0;  

      var writeOut = historiographer.writeAccelerometer(x,y,z,deltaTime);
      if(writeOut == true){
        writeToFlash();
      }
      accelerometerSkip = 0;
    }    
    else{
      accelerometerSkip++;
    }
  }
}

var magnetude = 0;
var magnetudeSkip = 0;
function onMagnetude(a){
  if(started){
    if(magnetudeSkip == magnetudeSkips[selectedMagnetude]){
      var timestamp = Math.round(Date.now());
      var deltaTime = timestamp - lastTimestamp;
      lastTimestamp = timestamp;
      var mag = a.mag * 8192.0;

      var writeOut = historiographer.writeMagnetude(mag,deltaTime);
      if(writeOut == true){
        writeToFlash();
      }
      magnetudeSkip = 0;
    }
    else{
      magnetudeSkip++;
    }
  }
}

function configureSensors(){
  if(fastUpdateIntervall == true){
    Bangle.setPollInterval(10);
  }
  if(selectedHRM != 0){
    let options = Bangle.getOptions();
    options.hrmPollInterval = hrmSpeeds[selectedHRM];
    Bangle.setOptions(options);
    Bangle.setHRMPower(true, appID);
    historiographer.setHRM(true);
    hrmActive = true;
  }
    
  if(selectedGPSspeed != 0){
    Bangle.setGPSPower(1);
    gpsActive = true;
    historiographer.setGPS(true);
    if(powersavingGPS==true){
       gpsTurnOnIntervallFunction=setInterval(gpsTurnON,GPSspeed[selectedGPSspeed]*1000);
    }
  }
    
  if(selectedBarometer != 0){
    Bangle.setBarometerPower(1, appID);
    barometerActive = true;
    historiographer.setBarometer(true);
  }
    
  if(selectedCompass!= 0){
    Bangle.setCompassPower(1, appID);
    compassActive = true;
    historiographer.setCompass(true);
  }
    
  if(selectedMagnetude!= 0){
    powerMagnetude = true;
    historiographer.setMagnetude(true);
  }
    
  if(selectedAccelerometer!= 0){
    powerAccelerometer = true;
    historiographer.setAccelerometer(true);
  }
}

function writeConfiguration(){
  
  require("Storage").erase("user.bin");
  require("Storage").compact(true);
  
  writeBuffer = new ArrayBuffer(maxIndex);
  writeBufferDataView = new DataView(writeBuffer);
  writeBufferAddr = E.getAddressOf(writeBufferDataView.buffer,true);
  
  historiographer.initArray(writeBufferAddr, maxIndex);
  writeNames();
  configureSensors();
  historiographer.writeIDsToArray();
  historiographer.writeOptions1(recordAltitude,jsMath, outputXML);
  historiographer.writeOptions2(filenameSupervisor,filenameSubject, filenameDate);
  var time = Math.round(Date.now());
  lastTimestamp = time;
  var date = Date(time);
  historiographer.writeDate(date.getFullYear(), date.getMonth(), date.getDate());
  var writeOut = historiographer.writeTime(date.getHours(), date.getMinutes());

  if(writeOut == true){
    writeToFlash();
  }

  Bangle.buzz();
  Bangle.buzz();
  started = true;
}

Bangle.on('GPS',onGPS);
Bangle.on('pressure', onBarometer);
Bangle.on('accel', function(accelEvent) {
  if(started){
    if(powerAccelerometer){
      onAccel(accelEvent);
    }

    if(powerMagnetude){
      onMagnetude(accelEvent);
    }
  }
});
Bangle.on('mag',onCompass);
Bangle.on('HRM-raw', onHRM);

let lastTimestamp = 0;

var hrmSpeeds = ["Off",10,20,40,80,160,200];
var hrmSpeedsText = ["Off","10ms","20ms","40ms","80ms","160ms","200ms"];
var selectedHRM = 0;

var barometerSkips = ["Off",0,1,2,3,5,10,20,50];
var barometerSkipsText = ["Off",0,1,2,3,5,10,20,50];
var selectedBarometer = 0;

var magnetudeSkips = ["Off",0,1,2,3,5,10,20,50];
var magnetudeSkipsText = ["Off",0,1,2,3,5,10,20,50];
var selectedMagnetude = 0;

var accelerometerSkips = ["Off",0,1,2,3,5,10,20,50];
var accelerometerSkipsText = ["Off",0,1,2,3,5,10,20,50];
var selectedAccelerometer = 0;

var compassSkips = ["Off",0,1,2,3,4,5,10,20,40];
var compassSkipsText =["Off",0,1,2,3,4,5,10,20,40];
var selectedCompass = 0;

var GPSspeed = ["Off",0,29,59,899,1799,3599];
var GPSspeedText = ["Off","1s","30s","1min","15min", "30min", "1h" ];
var selectedGPSspeed = 0;

var num = 9000;
var profiles = require("Storage").readJSON("availableConfigs.json", true).configs;
profiles.unshift("Custom");

var currentProfile = profiles[0];
var passphrase = "test";
let startedVisual = false;

function loadProfile(id){
  
  if(id != 0){
    currentProfile = profiles[id];

    var setting = require("Storage").readJSON(currentProfile+".json", true);
    supervisorname = setting.supervisorname;

    FILESIZE = setting.fileSize *1024;
    maxIndex = setting.ramSize;

    hrmSpeedsText = setting.hrmText;
    selectedHRM = setting.hrmSpeed;

    barometerSkips = setting.barometerSkips;
    barometerSkipsText = setting.barometerSkipsText;
    selectedBarometer = setting.barometer;

    magnetudeSkips = setting.magnetudeSkips;
    magnetudeSkipsText = setting.magnetudeSkipsText;
    selectedMagnetude = setting.magnetude;

    accelerometerSkips = setting.accelerometerSkips;
    accelerometerSkipsText = setting.accelerometerSkipsText;
    selectedAccelerometer = setting.accelerometer;

    compassSkips = setting.compassSkips;
    compassSkipsText = setting.compassSkipsText;
    selectedCompass = setting.compass;

    GPSspeed = setting.gPSspeedSeconds;
    GPSspeedText = setting.gPSspeedText;
    selectedGPSspeed = setting.gpsSpeed;
    powersavingGPS = setting.gpsEnergysaving;

    batteryNotifiyPercent = setting.batteryNotifiy;
    if(batteryNotifiyPercent){batteryNotifiyAction = true;}
    storageNotifiy = setting.storageNotifiy * 1024;
    if(storageNotifiy){storageNotifiyAction = true;}
    batterySavePercent = setting.energySaving;
    storageSave = setting.storageSaving * 1024;
    powerTurnoffBattery = setting.turnOffEnergy;
    if(powerTurnoffBattery){batterySaveAction = true;}
    powerTurnoffStorage = setting.turnOffStorage;
    if(powerTurnoffStorage){storageSaveAction = true;}
    passphrase = setting.unlockPhrase;
    reloadMenus();
  }
  else{
    currentProfile = profiles[0];
  }
}
// First menu
var mainmenu = {
  "" : { "title" : "Main Menu" },
  "< Back" : function() { load(); },
  "Start" : function() {
    E.showMenu(submenuClock);
    WIDGETS["widhistorio"].setActive();
    writeConfiguration();
    draw();
  },
  "Supervisor" : function() {
    E.showMenu();
    require("textinput").input({text:supervisorname}).then(result => {
      console.log("The user entered: ", result);
      supervisorname = result;
      E.showMenu(mainmenu);
    });
  },
  "Subject" : function() {
    require("textinput").input({text:subjectname}).then(result => {
      console.log("The user entered: ", result);
      subjectname = result;
      E.showMenu(mainmenu);
    });
  },
  "Profile: " : {
      value: 0,
      min: 0, max: profiles.length-1,
      format: v => profiles[v],
      onchange: v => {
        loadProfile(v);
      }
  },
  "Settings": function(){E.showMenu(menuSettings);},
  "Output": function(){E.showMenu(submenuOutputSettings);},
  "UnlockPhrase": function(){
     require("textinput").input({text:passphrase}).then(result => {
      console.log("The user entered: ", result);
       passphrase = result;
       E.showMenu(mainmenu);
    });
  },
  "Exit" : function() { load(); }, // remove the menu
};

var submenuStorageSavingDevices;
var submenuBatterySavingDevices;
var unlockScreen;
var submenuClock;
var submenuBatterySaving;
var submenuStorageSaving;
var submenuNotify;
var submenuSensors;
var menuSettings;
var submenuOutputSettings;

function reloadMenus(){
menuSettings = {
  "" : { "title" : "Settings" },
  "< Back" : function() { E.showMenu(mainmenu); },
  "Storage (in KB)" : {
    value : FILESIZE/1024,
    min:0,max:6144,step:128,
    onchange : v => {
      FILESIZE = v*1024;
    }
      }, 
  "Ramsize" : {
    value : maxIndex,
    min:0,max:6144,step:256,
    onchange : v => {
      maxIndex = v;
    }
      }, 
  "Sensors" : function() { E.showMenu(submenuSensors); },
  "Notify":function() { E.showMenu(submenuNotify); },
  "Energy savings": function() { E.showMenu(submenuBatterySaving); },
  "Storage savings": function() { E.showMenu(submenuStorageSaving); },
  
};
submenuSensors = {
  "" : { "title" : "Sensors" },
  "< Back" : function() { E.showMenu(menuSettings); },
  "HRM" : {
      value: selectedHRM,
      min: 0, max: hrmSpeedsText.length-1,
      format: v => hrmSpeedsText[v],
      onchange: v => {
        selectedHRM = v;
      }
      }, 
  "GPS" : {
      value: selectedGPSspeed,
      min: 0, max: GPSspeedText.length-1,
      format: v => GPSspeedText[v],
      onchange: v => {
          selectedGPSspeed = v;
      }
  },
  "Energy Save GPS" : {
    value : powersavingGPS,
    onchange : v => { powersavingGPS=v; }
  },
  "Skip Baro." : {
      value: selectedBarometer,
      min: 0, max: barometerSkipsText.length-1,
      format: v => barometerSkipsText[v],
      onchange: v => {
          selectedBarometer = v;
    }
      },
  "Skip Accel." : {
      value: selectedAccelerometer,
      min: 0, max: accelerometerSkipsText.length-1,
      format: v => accelerometerSkipsText[v],
      onchange: v => {
          selectedAccelerometer = v;
    }
      },
  "Skip Mag." : {
      value: selectedMagnetude,
      min: 0, max: magnetudeSkipsText.length-1,
      format: v => magnetudeSkipsText[v],
      onchange: v => {
          selectedMagnetude = v;
    }
      },
  "Skip Compass" : {
      value: selectedCompass,
      min: 0, max: compassSkipsText.length-1,
      format: v => compassSkipsText[v],
      onchange: v => {
          selectedCompass = v;
      }
  }
};
submenuNotify = {
  "" : { "title" : "Notify" },
  "< Back" : function() { E.showMenu(menuSettings); },
  "Storage (in KB)" : {
    value : storageNotifiy,
    min:0,max:6144,step:128,
    onchange : v => {
      storageNotifiyAction = true;
      storageNotifiy = v * 1024;
    }
      }, 
  "Battery" : {
    value : batteryNotifiyPercent,
    min:0,max:100,step:5,
    onchange : v => {
      batteryNotifiyAction = true;
      batteryNotifiyPercent = v;
    }
      }
};
submenuStorageSaving = {
  "" : { "title" : "Saving" },
  "< Back" : function() { E.showMenu(menuSettings); },
  "Storage (in KB)" : {
    value : storageSave,
    min:0,max:6144,step:128,
    onchange : v => {
      batterySaveAction = true;
      storageSave = v * 1024;
    }
      }, 
  "Sensors to Stop" : function() { E.showMenu(submenuStorageSavingDevices); },
};
submenuBatterySaving = {
  "" : { "title" : "Saving" },
  "< Back" : function() { E.showMenu(menuSettings); },
  "Battery" : {
    value : batterySavePercent,
    min:0,max:100,step:5,
    onchange : v => {
      batterySaveAction = true;
      batterySavePercent = v;
    }
      },
  "Sensors to Stop" : function() { E.showMenu(submenuBatterySavingDevices); },
  "10 ms Updates" : {
    value : fastUpdateIntervall,
    onchange : v => { fastUpdateIntervall = v;}
  }
};

submenuClock = {
  "< Back" : function() { 
      clearTimeout(drawTimeout);
      E.showMenu(unlockScreen);
      clearTimeout(drawTimeout);
                        }
};
unlockScreen = {
  "Unlock & Stop" : function() { 
    E.showMenu();
    require("textinput").input({text:""}).then(result => {
      console.log("The user entered: ", result);
      if(result == passphrase){
        started = false;
        
        var timestamp = Math.round(Date.now());
        var deltaTime = timestamp - lastTimestamp;
        lastTimestamp = timestamp;
        
        var overflow = historiographer.writeEndID(deltaTime)
        writeToFlash();
        if(overflow == false){
          writeToFlash();
        }
        
        WIDGETS["widhistorio"].reset();
        
        E.showMenu(mainmenu);
      }
      else{
        E.showMenu(unlockScreen);
      }
    });
                        },
  "Clock" : function() {
    E.showMenu(submenuClock);
    draw();
                        },
};


submenuBatterySavingDevices = {
  "" : { "title" : "Shutoff" },
  "< Back" : function() { E.showMenu(mainmenu); },
  "HRM" : {
    value : powerTurnoffBattery[0],
    onchange : v => { powerTurnoffBattery[0]=v; }
  },
  "Barometer" : {
    value : powerTurnoffBattery[1],
    onchange : v => { powerTurnoffBattery[1]=v; }
  },
  "Accelerometer" : {
    value : powerTurnoffBattery[2],
    onchange : v => { powerTurnoffBattery[2]=v; }
  },
  "Magnetude" : {
    value : powerTurnoffBattery[3],
    onchange : v => { powerTurnoffBattery[3]=v; }
  },
  "Compass" : {
    value : powerTurnoffBattery[4],
    onchange : v => { powerTurnoffBattery[4]=v; }
  },
  "GPS" : {
    value : powerTurnoffBattery[5],
    onchange : v => { powerTurnoffBattery[5]=v; }
  },
};
submenuOutputSettings = {
  "" : { "title" : "Output" },
  "< Back" : function() { E.showMenu(mainmenu); },
  "RecordHeight" : {
    value : recordAltitude,
    onchange : v => {
      recordAltitude = v;
    }
      },
  "JSMath" : {
    value : jsMath,
    min:0,max:100,step:5,
    onchange : v => {
      jsMath = v;
    }
      },
  "XML" : {
    value : outputXML,
    onchange : v => {
      outputXML = v;
    }
      },
  "File Supervisor" : {
    value : filenameSupervisor,
    onchange : v => {
      filenameSupervisor = v;
    }
      },
  "File Subject" : {
    value : filenameSubject,
    onchange : v => {
      filenameSubject = v;
    }
      },
  "File Date" : {
    value : filenameDate,
    onchange : v => {
      filenameDate = v;
    }
      },
};
submenuStorageSavingDevices = {
  "" : { "title" : "Shutoff" },
  "< Back" : function() { E.showMenu(submenuStorageSaving); },
  "HRM" : {
    value : powerTurnoffStorage[0],
    onchange : v => { powerTurnoffStorage[0]=v; }
  },
  "Barometer" : {
    value : powerTurnoffStorage[1],
    onchange : v => { powerTurnoffStorage[1]=v; }
  },
  "Accelerometer" : {
    value : powerTurnoffStorage[2],
    onchange : v => { powerTurnoffStorage[2]=v; }
  },
  "Magnetude" : {
    value : powerTurnoffStorage[3],
    onchange : v => { powerTurnoffStorage[3]=v; }
  },
  "Compass" : {
    value : powerTurnoffStorage[4],
    onchange : v => { powerTurnoffStorage[4]=v; }
  },
  "GPS" : {
    value : powerTurnoffStorage[5],
    onchange : v => { powerTurnoffStorage[5]=v; }
  },
};
}

Bangle.on('touch', function(button, xy) {
  if(showingWarning){
    if(xy.x > 30 && xy.x < 140)
    {
      if(xy.y > 120)
      {
        E.showMenu(submenuClock);
        draw();
      }
    }
  }
  if(noMoreStorage){
    if(xy.x > 30 && xy.x < 140)
    {
      if(xy.y > 120)
      {
        load();
      }
    }
  }
});

var fullStorage = function(){
  g.clear(true);

  g.setFont("Vector",15);
  g.drawString("Please return to", 5,30,true);
  g.drawString("Supervisor", 5,50,true);
  g.drawString("Storage is full", 5,80,true);

  g.drawRect(40,130,130,170);
  g.setFont("Vector",20);
  g.drawString("OK",70,140);

  noMoreStorage = true;
};

var warnings = function(){
  showingWarning = true;
  g.clear(true);

  g.setFont("Vector",15);
  g.drawString("Please visit Supervisor", 5,110,true);

  if(file.offset > storageNotifiy)
  {
    g.drawString("Low storage", 5,30,true);
    WIDGETS["widhistorio"].setStorageState(1);
    storageNotifiyAction = false;
  }
  if(E.getBattery()<batteryNotifiyPercent)
  {
    g.drawString("Low battery", 5,50,true);
    WIDGETS["widhistorio"].setBatteryState(1);
    batteryNotifiyAction = false;
  }
  if(file.offset > storageSave)
  {
    g.drawString("Very low storage", 5,70,true);
    WIDGETS["widhistorio"].setStorageState(2);
  }
  if(E.getBattery() < batterySavePercent)
  {
    WIDGETS["widhistorio"].setBatteryState(2);
    g.drawString("Very low battery", 5,90,true);
  }
  g.drawRect(40,130,130,170);
  g.setFont("Vector",20);
  g.drawString("OK",70,140);
};
reloadMenus();
Bangle.loadWidgets();
Bangle.drawWidgets();
var m = E.showMenu(mainmenu);
