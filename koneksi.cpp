#include "setup.h"

String wifiSSID = "give";
String password = "okok1234";

void koneksiWiFi()
{
    Serial.print("\n\nConnecting ");

    WiFi.begin(wifiSSID.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.print("\nconnected to WiFi, SSID: ");
    Serial.println(WiFi.SSID());
    // Serial.println("RSSI       : " + String(WiFi.RSSI()));
    // Serial.println("Address    : " + WiFi.macAddress());
    // Serial.println("IP local   : " + WiFi.localIP().toString());
    // Serial.println("IP Gateway : " + WiFi.gatewayIP().toString());
    // Serial.println("DNS        : " + WiFi.dnsIP().toString());
}