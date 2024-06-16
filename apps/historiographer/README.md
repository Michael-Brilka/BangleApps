# Historiographer
The goal of the Historiographer-App is to enable long-term recordings of sensor data on the Bangle.js 2. This is achieved by converting the data and saving the data in a custom binary format.

For decoding the file, the decoder application can be used.

## Workflow
![Process](https://github.com/Michael-Brilka/BangleApps/assets/33370237/b63d7932-ecb6-4e6d-a4a1-4668833ebbf3)


## Profiles
Profiles enable a fast way to set up the Historiographer app. Only the name of the subject and the output settings need to be changed.

An example of a profile can be found in the [profileExample folder](https://github.com/Michael-Brilka/BangleApps/tree/master/apps/historiographer/profileExample).

## Settings 
The following settings can be changed inside the settings menu:

* Size of file - Sets the size of the file during creation and is given in kilobytes.
* Size of RAM storage - Temporary storage for data. First write into RAM storage, and if it is full, copy the data to the flash. 768 or 1024 bytes offers the best balance.
* Selection of sensors and their interval - Selects the sensors that we monitor and defines a custom interval.
* Notification of the user regarding low storage or battery - First stage warning
* Shutdown of sensors during low storage - Second stage warning with the ability to disable the recording of sensors.
* Shutdown of sensors during low battery - Second stage warning with complete shutdown of a sensor

## Output
These settings control mainly the output of the decoded file. These settings are not set by a profile. The following settings can be changed inside the output menu:

* RecordHeight - Activating this saves the height directly to the flash instead of calculating it later.
* JSMath - Active only if RecordHeight is off. Activating this, the decoder uses, for the conversion from pressure to height, the math provided by Espurino.
* XML - Output file will be a single XML instead of multiple CSV files.
* File Supervisor - Adds the supervisor to the filename.
* File Subject - Adds the subject to the filename.
* File Date - Adds the date to the filename.
