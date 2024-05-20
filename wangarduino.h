#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

void loop()
{
    WiFiClient clientMSG;
    HTTPClient httpMSG;
    httpMSG.begin(clientMSG, "http://we.ngarduino.com/sendMessage.php");
    httpMSG.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String key = "t1vvd1GuN1cHZUb5UnbXNy5cexo3H6ET";    // masukin key nya
    String message = "Hello From Ngarduino";            // atur pesannya
    String data = "key=" + key + "&message=" + message; // data pesan
    int httpCode = httpMSG.POST(data);                  // api ngirim pesan
    String payload = httpMSG.getString();
    Serial.println(payload);
    httpMSG.end();
    delay(60000);
}