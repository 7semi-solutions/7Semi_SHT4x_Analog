# 🚀 7Semi_SHT4x_analog
A lightweight and minimal Arduino library for the **Sensirion SHT40I-Analog temperature + humidity sensor family**.
Supports all analog-output variants (HD1B, ID1B, JD1B, KD1B, LD1B) and converts the sensor’s analog RH/T voltages into real-world **%RH** and **°C / °F** values.  
Designed for **low flash usage** and compatible with **AVR, ESP32, ESP8266, RP2040, STM32**, and other Arduino platforms.

![Arduino](https://img.shields.io/badge/platform-arduino-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg)
---

## ✨ Features

### ✔ Supports all SHT40I-Analog variants
- **HD1B** – standard linear output  
- **ID1B** – industrial RH + table-based T  
- **JD1B** – industrial RH + standard T  
- **KD1B** – humidity-only  
- **LD1B** – table-based RH + T  

### ✔ Conversion Capabilities
- **Analog RH output → %RH**  
- **Analog T output → °C / °F**

### ✔ Library Highlights
- Customizable ADC resolution (8/10/12/13/16-bit)
- Simple API:
  - `readHumidity()`
  - `readTemperatureC()`
  - `readTemperatureF()`
- Works with 3.3V or 5V sensors
- Extremely small footprint — ideal for embedded systems
- Pure analog — **no I²C required**

---

## ⚡ Getting Started
### 1. Install via Arduino Library Manager
1. Open Arduino IDE  
2. Navigate to:  
   - **IDE 1.x:** `Sketch > Include Library > Manage Libraries…`  
   - **IDE 2.x:** Library Manager sidebar  
3. Search for: 7Semi SHT4x analog
4. 
4. Click **Install**

### 2. Include the library
```cpp
#include <SHT4x_analog_7Semi.h>
```
## 🔌 Wiring (Analog)

| SHT40I-Analog Pin | Arduino Pin        |
| ----------------- | ------------------ |
| VDD               | 3.3V               |
| GND               | GND                |
| AOUT-RH           | A0 (or any analog) |
| AOUT-T            | A1 (or any analog) |


Note: Some variants such as **KD1B** do not provide a temperature output pin.

