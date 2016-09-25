/*
- Användning

-- Custom lib
Skapa Arduino/libraries/GoPro8266/
                                  - GoPro8266.h
                                  - GoPro8266.cpp

-- Exempelkod
#include "GoPro8266.h"

GoPro8266 gp("GOPRONAME", "GOPROPASS", "10.5.5.9", 9);

void setup() {
  gp.connect();
}

void loop() {
  delay(500);
}
*/

#ifndef GoPro8266_h
#define GoPro8266_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

class GoPro8266
{
  public:
    GoPro8266(char* ssid, char* password, char* GoProIP, int GoProPort, bool debug = false);
    
    bool connect();
    bool status();
    bool trigger();
    bool stop();
    bool sleep();
    void wake();
  
  private:
    bool httpGET(String url);

    const char* _ssid;
    const char* _password;
    const char* _GoProIP;
    int         _GoProPort;
    bool        _debug;
};

#endif