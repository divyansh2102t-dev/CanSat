# 🔌 CanSat 2026: Pinout & Wiring Connections
**Team**: Team Alpha (CAN-Team-07)  
**Target Board**: ESP32 DevKit V1 (30-pin / 36-pin)

---

## 1. Master Pin Connection Table

| Peripheral | Sensor / Module Pin | ESP32 DevKit Pin | Wire Color Code | Notes / Function |
|---|---|---|---|---|
| **Power** | Battery (+) | Switch Terminal 1 | Red | From 3.7V LiPo or 5V Powerbank |
| | Switch Terminal 2 | ESP32 `VIN` / `5V` | Red | Powers the onboard 3.3V LDO |
| | Battery (–) | ESP32 `GND` | Black | Common ground |
| **Status LED** | Anode (+) with 220Ω | `GPIO 4` | Yellow | Mandatory Power & TX indicator |
| | Cathode (–) | `GND` | Black | Active indicator |
| **BMP180 / 280** | `VCC` | `3V3` | Red | 3.3V supply |
| | `GND` | `GND` | Black | Common Ground |
| | `SDA` | `GPIO 21` | Blue | Shared I2C Data bus |
| | `SCL` | `GPIO 22` | Green | Shared I2C Clock bus |
| **MPU6050** | `VCC` | `3V3` | Red | 3.3V supply |
| | `GND` | `GND` | Black | Common Ground |
| | `SDA` | `GPIO 21` | Blue | Shared I2C Data bus |
| | `SCL` | `GPIO 22` | Green | Shared I2C Clock bus |
| | `AD0` | `GND` | Black | Sets I2C address to 0x68 |
| **LoRa SX1278** | `VCC` | `3V3` | Red | **Must be 3.3V ONLY** |
| | `GND` | `GND` | Black | Common Ground |
| | `NSS` / `CS` | `GPIO 5` | Orange | SPI Chip Select |
| | `SCK` | `GPIO 18` | White | SPI Serial Clock |
| | `MISO` | `GPIO 19` | Gray | SPI Master In Slave Out |
| | `MOSI` | `GPIO 23` | Purple | SPI Master Out Slave In |
| | `NRESET` / `RST` | `GPIO 14` | Brown | Reset Pin |
| | `DIO0` | `GPIO 2` | Yellow | Interrupt Pin |
| | `ANT` | 17.3cm wire or spring | — | 1/4 wave antenna for 433MHz |

---

## 2. Shared I2C Bus Note
Both the **BMP180** (I2C address `0x77`) and **MPU6050** (I2C address `0x68`) share the same I2C pins (`GPIO 21` for SDA and `GPIO 22` for SCL). Simply connect both SDA pins together to GPIO 21, and both SCL pins together to GPIO 22.

---

## 3. Ground Station Wiring (Receiver ESP32)
The Ground Station ESP32 only requires the SX1278 LoRa module wired to the same SPI pins:
* `NSS` -> `GPIO 5`
* `RST` -> `GPIO 14`
* `DIO0` -> `GPIO 2`
* `SCK` -> `GPIO 18`
* `MISO` -> `GPIO 19`
* `MOSI` -> `GPIO 23`
* `VCC` -> `3V3`, `GND` -> `GND`

Connect the Ground Station ESP32 to your laptop via USB cable at 115200 baud.\n