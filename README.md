# 🛰️ CanSat 2026 — Team Alpha (CAN-Team-07)
**Physics Club, SVNIT Surat — National Space Day 2026**

Complete, production-ready flight computer firmware, ground station receiver, standalone sensor verification tests, live web dashboard, and engineering documentation for the CanSat Competition 2026.

---

## 📁 Repository Structure

```
d:\Projects\CanSat\
├── README.md                           # Main Project Guide
├── docs/
│   ├── physical_calculations.md        # Parachute sizing, mass & impact calculations
│   ├── wiring_diagram.md               # Pinout mapping & schematics
│   └── competition_checklist.md        # Pre-launch and flight checklist
├── flight-computer/
│   └── flight_computer/
│       └── flight_computer.ino         # Main CanSat Transmitter Firmware
├── ground-station/
│   └── ground_station/
│       └── ground_station.ino          # LoRa Receiver (USB Serial Gateway)
├── sensor-tests/
│   ├── test_bmp180/
│   │   └── test_bmp180.ino            # BMP180 / BMP280 Barometer test
│   ├── test_mpu6050/
│   │   └── test_mpu6050.ino           # MPU6050 6-Axis IMU test
│   ├── test_lora_tx/
│   │   └── test_lora_tx.ino           # SX1278 433MHz Transmitter test
│   └── test_lora_rx/
│       └── test_lora_rx.ino           # SX1278 433MHz Receiver test
└── dashboard/
    └── index.html                      # Real-Time Telemetry Web Dashboard
```

---

## ⚡ Quick Start

### 1. Required Arduino Libraries
Open Arduino IDE -> **Tools -> Manage Libraries...** and install:
1. `LoRa` by Sandeep Mistry
2. `Adafruit BMP085 Library` (for BMP180 / BMP085) or `Adafruit BMP280 Library`
3. `Adafruit MPU6050`
4. `Adafruit Unified Sensor`

### 2. Uploading Firmware
1. Open `flight-computer/flight_computer/flight_computer.ino` in Arduino IDE.
2. Select Board: **ESP32 Dev Module** (or your ESP32 board).
3. Connect CanSat ESP32 via USB and click **Upload**.
4. Disconnect USB and power via battery and switch — telemetry will start transmitting automatically.

### 3. Launching the Live Telemetry Web Dashboard
1. Open `dashboard/index.html` in Google Chrome or Edge.
2. Plug your Ground Station ESP32 (running `ground-station/ground_station.ino`) into your laptop.
3. Click **🔌 Connect Ground Station** on the web page and select your ESP32's COM port.
4. Watch live altitude, descent speed, 3D attitude, and real-time graphs stream in real time!
5. After the flight, click **📥 Export CSV** to download the dataset for your 4-hour analysis report.

*(You can also click **🎮 Simulated Flight** in the dashboard to test all graphs and instruments without any hardware connected!)*

---

## 📡 Packet Protocol
Every transmitted packet strictly follows the Rulebook Section 7 specification:
```
CAN-Team-07; P-XXX; Ti-HH:MM:SS:MS; A-XXX.X; Pr-XXXX.XX; T-XX.X; Ro-XX.X; Pi-XX.X; Ya-XX.X; AX-XX.XX; AY-XX.XX; AZ-XX.XX;
```

---

## ⚖️ Key Engineering Parameters
* **Structure Size**: 20 cm height × 10 cm diameter (within $21 \times 12\text{ cm}$ rule)
* **Total Mass**: $330\text{ g}$ (within $500\text{ g}$ rule)
* **Parachute Diameter**: $90\text{ cm}$ hemispherical with $9\text{ cm}$ center spill hole
* **Descent Speed**: $3.5\text{ m/s}$ (rule: $\le 5.0\text{ m/s}$)
* **Flight Time**: $\sim 8.7\text{ seconds}$ from 100 ft drone drop
* **Egg Deceleration Force**: $\sim 10.15\text{ N}$ (well below $25\text{ N}$ fracture limit)\n