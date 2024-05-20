#include "setup.h"

// setup DHT11
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// variabel settings
Data_settings currentSettings;

String token;
int setToken = 1;
int derajatAC = 20;
int beda = 0;
int updateSuhu = 0;
int dangerRuangan = 3;
int tanda = 0;

const uint16_t kIrLed = 14;
IRDaikinESP ac(kIrLed);

void ac_on(int derajatAC)
{
  ac.on();
  ac.setFan(1);
  ac.setMode(kDaikinCool);
  ac.setTemp(derajatAC);
  ac.setSwingVertical(false);
  ac.setSwingHorizontal(false);
  // Serial.println(ac.toString());
  Serial.println("derajat ac: " + String(derajatAC));

#if SEND_DAIKIN
  ac.send();
#endif // SEND_DAIKIN
}

void ac_off()
{
  ac.off();
  Serial.println(ac.toString());
  // Now send the IR signal.
#if SEND_DAIKIN
  ac.send();
#endif // SEND_DAIKIN
}

void setup()
{
  Serial.begin(9600);
  koneksiWiFi();
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  ac.begin();
  ac_on(derajatAC);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  if (setToken == 1)
  {
    token = auth();
    setToken = 0;
  }

  // DHT11
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (token != "kosong")
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%  Temperature: ");
    Serial.print(t);
    Serial.println("°C ");
  }
  else if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
  }

  // pengecekan token
  static unsigned long previousTokenMillis = 0;
  const unsigned long tokenInterval = (1000 * 50) + (1000 * 60 * 2); // 2 menit 50 detik
  unsigned long currentMillis = millis();
  // Serial.println((unsigned int)&token, HEX);

  if (currentMillis - previousTokenMillis >= tokenInterval)
  {
    previousTokenMillis = currentMillis;
    setToken = 1;
    Serial.println("");
  }

  currentSettings = settings(token);
  if (t < currentSettings.tempOpt + currentSettings.toleranceTemp && t > currentSettings.tempOpt - currentSettings.toleranceTemp)
  {
    Serial.println("aman");
  }
  else
  {
    if (t > currentSettings.tempOpt + currentSettings.toleranceTemp)
    {
      beda = t - currentSettings.tempOpt + currentSettings.toleranceTemp;
      Serial.println(String(derajatAC));
      if (derajatAC - beda < 16)
      {
        updateSuhu = 16;
        derajatAC = updateSuhu;
        ac_on(updateSuhu);
      }
      else
      {
        updateSuhu = derajatAC - beda;
        ac_on(updateSuhu);
      }

      if (derajatAC == 16)
      {
        tanda = tanda + 1;
      }
      else if (tanda > 3)
      {
        // kirim pesan wa
        pesanWa();
        Serial.println("Temp Optimal: " + String(currentSettings.tempOpt));
        Serial.println("Temp Toleransi: " + String(currentSettings.toleranceTemp));
        Serial.println("Temp Ruangan telalu tinggi: " + String(t));
        tanda = 0;
      }
      delay(10000);
    }
    else if (t < currentSettings.tempOpt - currentSettings.toleranceTemp)
    {
      beda = currentSettings.tempOpt - currentSettings.toleranceTemp - t;
      if (derajatAC + beda > 31)
      {
        updateSuhu = 30;
        derajatAC = updateSuhu;
        ac_on(updateSuhu);
      }
      else
      {
        updateSuhu = derajatAC + beda;
        ac_on(updateSuhu);
      }
      if (derajatAC == 30)
      {
        tanda = tanda + 1;
      }
      else if (tanda > 3)
      {
        // kirim pesan wa
        pesanWa();
        Serial.println("Temp Optimal: " + String(currentSettings.tempOpt));
        Serial.println("Temp Toleransi: " + String(currentSettings.toleranceTemp));
        Serial.println("Temp Ruangan telalu tinggi: " + String(t));
        tanda = 0;
      }
      delay(10000);
    }
  }

  // int temperature = 13;?>
  // int relativeHumidity = 13;
  // Serial.println((unsigned int)&temperature, HEX);
  // Serial.println((unsigned int)&relativeHumidity, HEX);
  record(t, h, token);
  // delay(10000);
}

void pesanWa()
{
}