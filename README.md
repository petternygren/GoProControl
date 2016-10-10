# GoProControl
Header giving basic functionality for controling a GoPro4 with the "Adafruit Feather HUZZAH ESP8266" or 
"Adafruit Feather M0 wifi"
Interfacing via the GoPro built in hotspot and utilising the GoPro REST(ish) api: https://github.com/KonradIT/goprowifihack.

## How
The code are compiled with the arduino IDE. Follow this guide to get it set up:
https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide
https://learn.adafruit.com/adafruit-feather-m0-basic-proto/using-with-arduino-ide

* Creating a custom lib for arduino is done by creating a new folder @ Arduino/libraries/[some_folder]

* In this case create Arduino/libraries/GoPro8266

* Put GoPro8266.cpp and GoPro8266.h this folder then your good to go!

## Example
Use case for recoding 5 seconds of video every 1 minute:

```cpp
#include "GoProControl.h"

GoPro8266 gp("GOPRONAME", "GOPROPASS", "10.5.5.9", 9, true); //Initialize with debug mode active (will give some info in serial out).
bool connected;

void setup() {
  connected = gp.connect();
}

void loop() {
  if (connected) {
    bool ok;
  
    gp.wake(); //Wake the GoPro if its sleeping, otherwise nothing happens.

    ok = gp.status(); //Check GoPro status, is everything ok?

    if (ok) {ok = gp.videoModeOn();} //Make sure GoPro is in video mode.
    if (ok) {ok = gp.trigger();} //Trigger record.
    if (ok) {
      delay(5000); //Record 5 seconds of video
      ok = gp.stop(); //Stop record.
    }
    if (ok) {gp.sleep();} //Put GoPro to sleep.
    delay(60000); //Wait 1 minute then record another 5 seconds of video...
  }
  else {
    Serial.println("Not connected, nothing to do...");
    delay(60000);
  }
}
```