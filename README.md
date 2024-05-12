For more information regarding this project please refer to https://krishnaboopathy.bearblog.dev/gps-speedometer-prototype/

My 2015 KTM Duke is infamous for its stator coil burning out there by not able to produce the required voltage for the battery to be charged. But this time the coil holds good and it should be either the battery or the regulator unit which has to be root caused.

But meanwhile due to low battery level, the ECU won't be able to provide enough voltage to the speed sensor thereby the PWM output from the speedo is messed up. Thus the bike often shows "0" reading on the speedo console while speeding on the tarmac.

I have always wanted to build my own GPS based speedometer and wanted to explore how accurate these cheap modules are. So thought os usig the spare OLED modules that was lying around with the STM32 blue pill board populated with a STM32F103C8T6 Cortex-M3 MCU.

Modules Used:

    STM32F103C8T6 MCU
    NEO-6M GPS module with external active antenna
    0.96" OLED module with I2C interface
    Very cheap plastic box for enclosure

GPS Messages:
Any GPS module will have to c[omply with the NMEA standards and sends the co-ordinate data in specific formats. More info here I decided to use only the GPRMC data which contains almost every info that I require like the Latitude and Longitude, UTC date and time data and Speed on the ground.

There are various NMEA wrappers available on the web but I decided to go with my own very minimalist code to handle the job inside the ISR to reduce the code size and not to complicate matters.

But one issue with writing a minimalist code to parse the NMEA message is while the satellites are not locked the latitude and longitude data will be sent blank by the module and this has to be taken care which results in sub-standard coding. But its good enough for a prototype.

Display on OLED:
The common OLED modules are very reliable to display data over the I2C lines and using a tiny library that can handle the text and basic graphics should be suffice.

Observations:

    The data is always lagging by few seconds. When accelerating in a car at decent speeds, the speedo reading always leads the GPS speed by 3 to 4 kmph. When cruising at constant speed the GPS speeds are reliable.
    Satellite locking is good under open skies. But never hope to get a lock indoors. Even with ceramic and external active antenna I could never manage to get a satellite lock indoors.

Further Versions:

    The next version will be built over this with CAN interface to read the OBD data from the bike/car to display more statistics.
    This screen is good for testing but practicality is zero and the text is unreadable under sunlight.
