/*
GoPro8266.h - Arduino -> GoPro interface via http and udp.

Feel free to copy/modify or do whatever you like with his pice of code.
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
    bool videoModeOn();
    bool videoModeOff();
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