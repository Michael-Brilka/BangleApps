# HistoriographerB1
The goal of the HistoriographerB1-App is to enable long-term recordings of sensor data on the Bangle.js 1. This is achieved by converting the data and saving the data in a custom binary format.

For decoding the file, the decoder application can be used.

## Profiles
Profiles enable a fast way to set up the Historiographer app. Only the name of the subject and the output settings need to be changed.

An example of a profile can be found in the [profileExample folder](https://github.com/Michael-Brilka/BangleApps/tree/master/apps/historiographer/profileExample).

## Settings 
The following settings can be changed inside the settings menu:

* Size of file - Sets the size of the file during creation and is given in kilobytes.
* Size of RAM storage - Temporary storage for data. First write into RAM storage, and if it is full, copy the data to the flash. 768 or 1024 bytes offers the best balance.
* Selection of sensors and their interval - Selects the sensors that we monitor and defines a custom interval.
