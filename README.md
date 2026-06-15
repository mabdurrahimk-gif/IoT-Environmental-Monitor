# IoT Environmental Monitor

An ESP32-based device that monitors temperature, humidity, and air quality 
in real-time and displays the data on a live cloud dashboard.

## Features
- Real-time temperature and humidity monitoring (DHT11)
- Air quality monitoring (MQ-135)
- Live data visualization via ThingSpeak
- WiFi-enabled, accessible from anywhere

## Components Used
| Component | Purpose |
|-----------|---------|
| ESP32 | Main microcontroller, WiFi connectivity |
| DHT11 | Temperature & humidity sensor |
| MQ-135 | Air quality / gas sensor |

## How It Works
1. ESP32 reads sensor data every 20 seconds
2. Data is sent via HTTP to ThingSpeak
3. ThingSpeak displays live graphs on a dashboard

## Wiring Diagram
![Wiring Diagram](images/wiring_diagram.png)

## Dashboard
![ThingSpeak Dashboard](images/thingspeak_dashboard.png)

## Setup Instructions
1. Install Arduino IDE and ESP32 board support
2. Install libraries: DHT sensor library, Adafruit Unified Sensor
3. Create a `secrets.h` file with your WiFi and ThingSpeak credentials:
```cpp
   #define WIFI_SSID "your_wifi_name"
   #define WIFI_PASSWORD "your_wifi_password"
   #define THINGSPEAK_API_KEY "your_api_key"
```
4. Upload `code/environmental_monitor.ino` to your ESP32

## What I Learned
- Embedded programming with ESP32
- Sensor interfacing and wiring
- WiFi/HTTP communication
- Cloud data pipelines and dashboards
