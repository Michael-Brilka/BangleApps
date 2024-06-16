# Historiographer
The goal of the Historiographer-App is to enable long term recordings of sensor data on the Bangle.js 2. This is achived by converting the data and saving the data in a custom binary format.

For decoding the file the decoder application can be used.

## Workflow
![Process](https://github.com/Michael-Brilka/BangleApps/tree/master/apps/historiographer/Process.svg)

## Profiles
Profiles enable a fast way to setup the Historiographer app. 
Only the name of the subject and the output settings needs to be changed.

An example for a profiel can be found in the [profileExample folder](https://github.com/Michael-Brilka/BangleApps/tree/master/apps/historiographer/profileExample).

## Settings 
The folowing settings can be changed inside the settings menu:

* Size of file - Sets the size of the file during creation and is given in Kilobytes
* Size of RAM storage - Temporary storage for data. First write into RAM Storage and if it is full copy the data to the flash. 768 or 1024 Bytes offers the best balance. 
* Selection of sensors, and their interval - Selects the sensors which we monitor and we define a custom interval
* Notification of the User, regarding low storage or battery - First stage warning
* Shutdown of sensors during low storage - Second stage warning with the ability to disable the recording of sensors.
* Shutdown of sensors during low battery - Second stage warning with complete shutdown of a sensor

## Output
These settings controle mainly the output of the decoded file. These settings are not set by a profile. The following settings can be changed inside the output menu: 

* RecordHeight - Activating this saves the height directly to the flash, instead of calculating it later.
* JSMath - Active only if RecordHeight is off. Activating this, decoder uses, for the conversion from pressure to height, the Math provided by Espurino.
* XML - Output file will be a single XML instead of multiple CSV files
* File Supervisor - Adds the Supervisor to filename
* File Subject - Adds the Subject to filename
* File Date   - Adds the Date to filename
