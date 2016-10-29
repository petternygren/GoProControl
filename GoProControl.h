/*
GoProControl.h - Arduino -> GoPro interface via http and udp.

Feel free to copy/modify or do whatever you like with his pice of code.
*/

#ifndef GoProControl_h
#define GoProControl_h
#define WiFi101

#include "Arduino.h"
#ifdef WiFi101
  #include <WiFi101.h>
  #include <WiFiUdp.h>
#endif
#ifdef WiFi8266
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiUdp.h>
#endif

class GoProControl
{
  public:
    GoProControl(char* ssid, char* password, char* GoProIP, int GoProPort, bool debug = false);
    
    bool connect();
    bool status();
    bool videoModeOn();
    bool videoModeOff();
    bool trigger();
    bool stop();
    bool sleep();
    bool Settings();
    void wake();
  
  private:
    bool httpGET(String url);

    const char* _ssid;
    const char* _password;
    const char* _GoProIP;
    int         _GoProPort;
    bool        _debug;
    #ifdef WiFi101
      WiFiClient client;
    #endif
};

#endif