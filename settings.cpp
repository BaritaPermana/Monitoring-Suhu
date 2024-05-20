#include "setup.h"

Data_settings settings(const String &token)
{
    Data_settings settingsData;

    String url = "http://192.168.105.119/monsuko4/apiweb/record";
    HTTPClient http;   // Buat objek HTTPClient
    WiFiClient client; // Buat objek WiFiClient
    String response;

    http.begin(client, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Authorization", token);
    // Serial.println((unsigned int)&token, HEX);

    int httpResponseCode = http.GET();
    if (httpResponseCode == 200)
    {
        Serial.println("\nberhasil mengambil data setting");
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        // parsing json
        response = http.getString();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, response);
        if (!error)
        {
            JsonObject result = doc["result"][0];
            settingsData.tempOpt = result["tempOptimal"].as<int>();
            settingsData.toleranceTemp = result["toleranceTemp"].as<int>();
            settingsData.RHOpt = result["RHOptimal"].as<int>();
            settingsData.toleranceRH = result["toleranceRH"].as<int>();
        }
        else
        {
            Serial.print("Failed to parse JSON: ");
            Serial.println(error.c_str());
        }
    }
    else
    {
        Serial.println("\nGagal mengambil data setting");
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
    return settingsData;
}
