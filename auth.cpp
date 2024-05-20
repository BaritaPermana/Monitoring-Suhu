#include "setup.h"

String auth()
{
    String url = "http://192.168.105.119/monsuko4/apiWeb/auth";

    // buat objek
    WiFiClient client;
    HTTPClient http;

    // login
    String username = "espAdmin";
    String password = "barita";
    String token; // menampung nilai kembalian token

    String postData = "username=" + username + "&password=" + password;
    // String postData = "username=" + String(idUsers) +
    //                   "&password=" + String(temperature) +
    //                   "&relativeHumidity=" + String(relativeHumidity) +
    //                   "&idStatusTemp=" + String(idStatusTemp) +
    //                   "&idStatusRH=" + String(idStatusRH);

    // mengirim data
    http.begin(client, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode == 200)
    {
        Serial.println("connected to API,  resp: " + String(httpResponseCode));
        String response = http.getString();

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, response);

        if (!error)
        {
            // Ambil nilai token dari respons JSON
            token = doc["token"].as<String>();
        }
        else
        {
            Serial.println("Error parsing JSON");
        }
    }
    else
    {
        Serial.println("unconected to API,  resp: " + String(httpResponseCode) + "\n");
        token = "kosong";
    }

    http.end();
    return token;
}
