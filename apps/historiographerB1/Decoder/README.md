# HistoriographerB1-Decoder
The goal of the HistoriographerB1-App is to enable long-term recordings of sensor data on the Bangle.js 1. This is achieved by converting the data and saving the data in a custom binary format.
In order to decode the files we need to use a decoder to convert the binary files to a human readable format. This is done by this application.

#Compiling
First we need to generate the files for make. This is done by using the "cmake ." command from the terminal.
Next we can use the "make" command to generate the Historiographer-Decoder application.
It will generate the Historiographer-Decoder application which can be called from the terminal.

#Execution
For execution call the Historiographer-Decoder directly within the terminal together with the file you want to decode. E.g. "./HistoriographerDecoder FileToDecode.bin"
