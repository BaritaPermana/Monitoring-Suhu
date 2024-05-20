// setup
#ifndef GET_FUNCTION_H
#define GET_FUNCTION_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
// #include <ESP8266Ping.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// inframerah
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Daikin.h>
// DHT11
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

struct Data_settings
{
    int tempOpt;
    int RHOpt;
    int toleranceTemp;
    int toleranceRH;
};

void koneksiWiFi();
String auth();
Data_settings settings(const String &);
void record(int &, int &, String &);

#endif