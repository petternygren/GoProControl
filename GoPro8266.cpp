#include "GoPro8266.h"

GoPro8266::GoPro8266(char* ssid, char* password, char* GoProIP, int GoProPort, bool debug) {
    _ssid      = ssid;
    _password  = password;
    _GoProIP   = GoProIP;
    _GoProPort = GoProPort;
    _debug     = debug;

    if (_debug) {
      //Om debug är true aktiveras debug/info utskrifter
      Serial.begin(115200);
    }
}

bool GoPro8266::connect() {
  //Anslut till GoPro hotspot
    
  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (_debug) {
      Serial.println("Trying to connect, current status: ");
      Serial.print(WiFi.status());
      }
    }
  if (WiFi.status() == WL_CONNECTED) {
    if (_debug) {Serial.println("Connected");}
    return true;
  }
  else {
    if (_debug) {Serial.println("Failed to connect");}
    return false;
  }
}

void GoPro8266::wake() {
  //Skickar WakeOnLan(wol) signal

  WiFiUDP udp; //wol skickas via UDP

  if (udp.begin(_GoProPort) == 1) { //Är önskad port tillgänglig?
    if (_debug) {Serial.println("UDP port open");}
    
    /*
    Bygg wol "magicpackage"
    
    "6 bytes of all 255 (FF FF FF FF FF FF in hexadecimal),
    followed by sixteen repetitions of the target computer's 48-bit MAC address,
    for a total of 102 bytes."

    GoPro behöver dock inte MAC adressen för att vakna. Därför skickas enbart första delen.
    */
    char magicP[102];
    //6 Bytes with 0xFF
    for (int i=0;i<6;i++)
        magicP[i] = 0xff;
    
    udp.beginPacket(_GoProIP, _GoProPort);
    udp.write(magicP);
    udp.endPacket();
    udp.stop();
  }
  else {
    if (_debug) {Serial.println("Failed to open UDP port");}
  }
}

bool GoPro8266::httpGET(String url) {
  //Skicka GET request via http
  
  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  http.end();

  if (httpCode == 200) {
    return true;
  }
  else {
    return false;
  }
}

bool GoPro8266::status() {
  return httpGET("http://" + String(_GoProIP) + "/gp/gpControl/status");
}

bool GoPro8266::videoModeOn() {
  return httpGET("http://" + String(_GoProIP) + "/gp/gpControl/setting/10/1");
}

bool GoPro8266::videoModeOff() {
  return httpGET("http://" + String(_GoProIP) + "/gp/gpControl/setting/10/0");
}

bool GoPro8266::trigger() {
  return httpGET("http://" + String(_GoProIP) + "/gp/gpControl/command/shutter?p=1");
}

bool GoPro8266::stop() {
  return httpGET("http://" + String(_GoProIP) + "/gp/gpControl/command/shutter?p=0");
}

bool GoPro8266::sleep() {
  return httpGET("http://" + String(_GoProIP) + "/gp/gpControl/command/system/sleep");
}