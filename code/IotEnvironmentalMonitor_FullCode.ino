#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include "secrets.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ135PIN 34

DHT dht(DHTPIN, DHTTYPE);


const char* ssid     = WIFI_SSID;
const char* password = WIFI_PASSWORD;
String apiKey = THINGSPEAK_API_KEY;

const char* server = "http://api.thingspeak.com/update";

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int airQuality = analogRead(MQ135PIN);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read DHT11!");
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("°C | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Air Quality: ");
  Serial.println(airQuality);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey +
                  "&field1=" + String(temperature) +
                  "&field2=" + String(humidity) +
                  "&field3=" + String(airQuality);

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak!");
    } else {
      Serial.println("Error sending data");
    }
    http.end();
  }

  delay(20000); // ThingSpeak free tier requires 15+ sec between updates
}
