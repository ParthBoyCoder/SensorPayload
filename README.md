# Environmental Multi-Sensor Payload Unit

A portable real-time environmental monitoring system built using **Arduino Nano**, integrating multiple sensors to capture and display live environmental and location data.

---

## Features

* 📡 Real-time sensor data output via Serial Monitor
* 🌡️ Temperature & Humidity measurement
* 🌫️ Air quality monitoring
* 📊 Atmospheric pressure estimation (sea-level model)
* 📍 GPS-based location tracking (Latitude, Longitude, Altitude)
* 🕒 GPS-synced Date & Time
* 🔗 Multi-sensor integration on a single microcontroller

---

## System Overview

This project combines multiple sensors into a single embedded system:

| Sensor     | Function                         |
| ---------- | -------------------------------- |
| DHT11      | Temperature & Humidity           |
| MQ135      | Air Quality (analog)             |
| HX710B     | Atmospheric Pressure (ADC-based) |
| NEO-6M GPS | Location + Time                  |

All sensor data is processed and displayed in real-time through the Arduino Serial Monitor.

---

## Hardware Used

* Arduino Nano
* DHT11 Sensor
* MQ135 Gas Sensor
* HX710B Pressure Module (with built-in sensing element)
* NEO-6M GPS Module
* Breadboard & Jumper Wires

---

## Wiring Summary

### DHT11

* VCC → 5V
* GND → GND
* DATA → D7

### MQ135

* VCC → 5V
* GND → GND
* AOUT → A0

### HX710B

* VCC → 5V
* GND → GND
* SCK → D5
* DOUT → D4

### GPS (NEO-6M)

* VCC → 5V
* GND → GND
* TX → D2
* RX → D3

---

## 💻 Software & Libraries

* Arduino IDE
* TinyGPSPlus
* DHT Sensor Library
* SoftwareSerial

---

## Sample Output

```
Temp: 30.20 °C | Humidity: 49.00% | MQ135: 98 | Pressure: 101950 Pa  
Latitude: 22.583751  
Longitude: 88.302429  
Altitude: 0.00 m  
Date: 22/11/2025  
Time: 05:50:37
```

---

## Working Principle

* The **DHT11** provides temperature and humidity readings.
* The **MQ135** outputs an analog signal representing air quality.
* The **HX710B** reads pressure variations via a built-in sensing element and converts raw ADC values into Pascals using a sea-level baseline model.
* The **GPS module** continuously streams NMEA data, which is decoded using TinyGPSPlus to obtain location and time.

All values are synchronized and printed in a structured format.

---

## Applications

* Environmental monitoring
* Air quality analysis
* Weather trend observation
* Portable sensing systems
* Embedded systems learning

---

## Future Improvements

* 📱 Bluetooth / WiFi data transmission
* 📊 Data logging (SD card / cloud)
* 📟 OLED display integration
* 🌐 Web dashboard visualization
* 📉 Sensor data smoothing & filtering
* 📍 Altitude correction using pressure

---

## Author

**Parthib Banerjee**
Aspiring Robotics Engineer | Embedded Systems Enthusiast

---

## ⭐ Notes

* Pressure values are estimated using a **sea-level baseline model** (no external calibration).
* MQ135 values are raw and can be calibrated for specific gases if required.
* GPS altitude may be inaccurate indoors due to weak satellite signals.
* This project I made quite a while ago (I was 14 lol)

---

## Video

https://www.youtube.com/shorts/rcLUpOAlHU0?feature=share

---
