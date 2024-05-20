#include "setup.h"

void record(int &temperature, int &relativeHumidity, String &token)
{

    String url = "http://192.168.105.119/monsuko4/apiWeb/record";

    // buat objek
    HTTPClient http;
    WiFiClient client;

    String postData = "temperature=" + String(temperature) + "&relativeHumidity=" + String(relativeHumidity);
    // Serial.println((unsigned int)&temperature, HEX);
    // Serial.println((unsigned int)&relativeHumidity, HEX);

    // mengambil data
    http.begin(client, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Authorization", token);
    Serial.println("\nmengirim data");
    int httpResponseCode = http.POST(postData);
    // Serial.println((unsigned int)&token, HEX);

    if (httpResponseCode == 201)
    {
        Serial.println("berhasil menyimpan data");
        Serial.print("Response code: ");
        Serial.println(httpResponseCode);
    }
    else
    {
        Serial.println("gagal menyimpan data");
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}
