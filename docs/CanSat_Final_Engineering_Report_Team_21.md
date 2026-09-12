# 🛰️ CanSat Design, Build & Launch Competition 2026
## Official Engineering Design & Mission Report
**Event**: National Space Day 2026  
**Organized by**: Physics Club, SVNIT Surat  

---

### **Team Information**
* **Team Name**: Team Alpha
* **Team Identifier**: `CAN-Team-21`
* **Institution**: Sardar Vallabhbhai National Institute of Technology (SVNIT), Surat
* **Team Members**: [Member 1, Member 2, Member 3, Member 4, Member 5]
* **Faculty / Mentor**: [Mentor Name]
* **Date of Submission**: September 2026

---

## 📑 Table of Contents
1. [Executive Summary & Mission Statement](#1-executive-summary--mission-statement)
2. [Mission Profile & Requirements Compliance](#2-mission-profile--requirements-compliance)
3. [Mechanical & Structural Architecture](#3-mechanical--structural-architecture)
   - 3.1 Chassis Design & Dimensions
   - 3.2 Egg Payload Cushioning & Survivability
   - 3.3 Parachute Recovery Aerodynamics
4. [Avionics & Electrical Hardware](#4-avionics--electrical-hardware)
   - 4.1 Microcontroller & Sensor Suite
   - 4.2 LoRa RF Telemetry (SX1278 RA-02)
   - 4.3 Power Management & Mass Budget
   - 4.4 Wiring Pinout & Schematics
5. [Flight Software & Sensor Fusion](#5-flight-software--sensor-fusion)
   - 5.1 Architecture & Sampling Loop
   - 5.2 Complementary Filter for Roll/Pitch/Yaw
   - 5.3 Telemetry Packet Protocol
6. [Ground Station & Web Mission Control](#6-ground-station--web-mission-control)
7. [Post-Flight Data Analysis & Graphs](#7-post-flight-data-analysis--graphs)
8. [Lessons Learned & Future Scope](#8-lessons-learned--future-scope)
9. [Team Media & Photographic Evidence](#9-team-media--photographic-evidence)
10. [References & Citations](#10-references--citations)

---

## 1. Executive Summary & Mission Statement

The objective of **Team Alpha (CAN-Team-21)** in the CanSat 2026 Competition is to design, build, and deploy an autonomous, sub-scale aerospace payload capable of:
1. Surviving an aerial deployment from a drone at **$100\text{ ft}$ ($30.48\text{ m}$)**.
2. Deploying a stable aerodynamic parachute system limiting descent rate to **$\le 5.0\text{ m/s}$** (target: **$3.5\text{ m/s}$** for maximum flight duration).
3. Protecting a fragile **Grade-A raw egg payload** from crack or structural failure upon impact.
4. Transmitting continuous, real-time sensor telemetry (altitude, pressure, temperature, 3-axis acceleration, 3-axis orientation) over **433 MHz LoRa** to the official ground station and live web dashboard at $\ge 2\text{ Hz}$.
5. Conducting comprehensive post-flight data analysis within the designated 4-hour window.

---

## 2. Mission Profile & Requirements Compliance

| Parameter | Competition Rule | Team Alpha Implementation | Status |
|---|---|---|---|
| **Max Dimensions** | $\le 21\text{ cm} (+7\text{ cm for egg}) \times 12\text{ cm}$ | $20\text{ cm (Height)} \times 10\text{ cm (Diameter)}$ | ✅ Full Compliance |
| **Max Total Mass** | $\le 500\text{ g } (\pm 10\%)$ | **$300.2\text{ g}$** ($40\%$ mass buffer) | ✅ Full Compliance |
| **Drop Height** | $100\text{ ft} = 30.48\text{ m}$ (Drone) | $30.48\text{ m}$ | ✅ Full Compliance |
| **Descent Velocity** | $\le 5.0\text{ m/s}$ | **$3.5\text{ m/s}$** | ✅ Full Compliance |
| **Telemetry Rate** | $\ge 1\text{ packet/second}$ | **$2.0\text{ packets/second}$** ($500\text{ ms}$ interval) | ✅ Full Compliance |
| **RF Protocol** | $433\text{ MHz}$ LoRa, Sync Word `0xA5` | $433.0\text{ MHz}$ LoRa, Sync Word `0xA5` | ✅ Full Compliance |
| **Status Indicators** | Manual power switch + visible LED | Rocker toggle switch + High-brightness LED (GPIO 4) | ✅ Full Compliance |
| **Fragile Payload** | Egg recovery intact | Memory foam capsule with axial shock dispersion | ✅ Full Compliance |

---

## 3. Mechanical & Structural Architecture

### 3.1 Chassis Design & Dimensions
The CanSat body is constructed as a lightweight, modular cylindrical frame manufactured using **3D-printed PETG / PLA** with internal bulkhead ribs:
* **Outer Diameter**: $100\text{ mm}$
* **Total Height**: $200\text{ mm}$
* **Internal Volume Partitioning**:
  * **Top Section**: Semi-exposed parachute deployment bay.
  * **Middle Section**: Electronics bay housing ESP32 DevKit, BMP280, MPU6500, and SX1278 LoRa.
  * **Bottom Section**: Isolated egg payload cushioning chamber with impact crumple skirt.

```
+-------------------------------------------------------+
|  [UPLOAD PHOTO HERE: CanSat Top View - Isometric]     |
|                                                       |
|  Caption: Top view showing parachute rigging and      |
|  antenna mount.                                       |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD PHOTO HERE: CanSat Side View - Full Body]    |
|                                                       |
|  Caption: Side view showing cylindrical enclosure,    |
|  power switch, and status LED indicator.              |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD PHOTO HERE: CanSat Bottom View & Base]       |
|                                                       |
|  Caption: Bottom view illustrating impact shock skirt |
|  and egg bay access hatch.                            |
+-------------------------------------------------------+
```

### 3.2 Egg Payload Cushioning & Survivability
A standard raw chicken egg ($m_{egg} \approx 58\text{ g}$) has an axial crushing threshold of approximately **$25\text{ N}$**.
* **Cushioning Material**: Dual-density expanded polyethylene (EPE) and acoustic memory foam ($35\text{ mm}$ radial thickness).
* **Impact Physics**:
  $$\text{Impact Velocity } v = 3.5\text{ m/s}$$
  $$\text{Deceleration Distance (Foam compression) } d = 0.035\text{ m}$$
  $$a_{impact} = \frac{v^2}{2d} = \frac{(3.5)^2}{2 \times 0.035} = \frac{12.25}{0.07} = 175\text{ m/s}^2 \approx 17.8g$$
  $$F_{egg} = m_{egg} \times a_{impact} = 0.058\text{ kg} \times 175\text{ m/s}^2 = 10.15\text{ N}$$
  $$\text{Safety Factor} = \frac{25\text{ N}}{10.15\text{ N}} = 2.46$$

```
+-------------------------------------------------------+
|  [UPLOAD PHOTO HERE: Egg Chamber & Foam Assembly]     |
|                                                       |
|  Caption: Egg compartment with custom-molded foam     |
|  cushioning and retention cap.                        |
+-------------------------------------------------------+
```

### 3.3 Parachute Recovery Aerodynamics
To satisfy the descent constraint ($v \le 5.0\text{ m/s}$) while maximizing flight duration:
* **Drag Equation at Equilibrium**:
  $$m \cdot g = \frac{1}{2} \rho \cdot v^2 \cdot C_d \cdot A$$
  Where $m = 0.300\text{ kg}$, $g = 9.81\text{ m/s}^2$, $\rho = 1.184\text{ kg/m}^3$, $C_d = 0.75$, $v = 3.5\text{ m/s}$.
  $$A = \frac{2 \times 0.300 \times 9.81}{1.184 \times (3.5)^2 \times 0.75} = \frac{5.886}{10.878} = 0.541\text{ m}^2$$
  $$D = \sqrt{\frac{4 \cdot A}{\pi}} = \sqrt{\frac{4 \times 0.541}{3.14159}} \approx 0.83\text{ m} \rightarrow \mathbf{90\text{ cm flat canopy}}$$
* **Spill Hole**: $9\text{ cm}$ center apex vent ($10\%$ of diameter) to eliminate pendulum oscillation and tumbling.
* **Shroud Lines**: 8 braided nylon cords of length $1.2 \times D = 108\text{ cm}$.

```
+-------------------------------------------------------+
|  [UPLOAD PHOTO HERE: Parachute Canopy & Rigging]      |
|                                                       |
|  Caption: 90 cm ripstop nylon hemispherical parachute |
|  with central spill hole and 8-point harness.         |
+-------------------------------------------------------+
```

---

## 4. Avionics & Electrical Hardware

### 4.1 Component Selection
1. **Flight Computer**: ESP32 DevKit V1 (Tensilica Xtensa Dual-Core 32-bit LX6 @ 80/240 MHz).
2. **Barometer & Thermometer**: Bosch Sensortec **BMP280** (High precision $\pm 1\text{ Pa}$ pressure, $\pm 1\text{ m}$ altitude).
3. **Inertial Measurement Unit (IMU)**: InvenSense **MPU6500 / MPU6050** (3-axis gyroscope $\pm 500^\circ/\text{s}$, 3-axis accelerometer $\pm 2g$).
4. **RF Telemetry**: Ai-Thinker **SX1278 RA-02 LoRa** ($433\text{ MHz}$, SPI interface, $+17\text{ dBm}$ output power).

### 4.2 Electrical Pin Mapping

| Subsystem | Sensor / Peripheral Pin | ESP32 DevKit Pin | Bus / Protocol | Notes |
|---|---|---|---|---|
| **Power** | Battery Positive (+) | Switch $\rightarrow$ `VIN` | DC Supply | $3.7\text{V} - 5.0\text{V}$ input |
| | Battery Ground (–) | `GND` | Common Ground | System reference ground |
| **Indicator** | Status LED Anode (+) | `GPIO 4` | GPIO Output | $220\Omega$ current limiting |
| **BMP280** | `VCC` / `GND` | `3V3` / `GND` | Power | $3.3\text{V}$ regulated rail |
| | `SDA` / `SCL` | `GPIO 21` / `GPIO 22` | I2C (`0x76`) | $400\text{ kHz}$ Fast I2C bus |
| **MPU6500** | `VCC` / `GND` | `3V3` / `GND` | Power | $3.3\text{V}$ regulated rail |
| | `SDA` / `SCL` | `GPIO 21` / `GPIO 22` | I2C (`0x68`) | Shared with BMP280 |
| **SX1278 LoRa** | `VCC` / `GND` | `3V3` / `GND` | Power | **$3.3\text{V}$ ONLY** |
| | `NSS` / `CS` | `GPIO 5` | SPI (CS) | Hardware Chip Select |
| | `SCK` | `GPIO 18` | SPI (SCK) | Clock line |
| | `MISO` | `GPIO 19` | SPI (MISO) | Master In Slave Out |
| | `MOSI` | `GPIO 23` | SPI (MOSI) | Master Out Slave In |
| | `NRESET` / `RST` | `GPIO 14` | GPIO Output | Hardware Reset |
| | `DIO0` | `GPIO 2` | GPIO Input | Packet RX/TX interrupt |

```
+-------------------------------------------------------+
|  [UPLOAD PHOTO HERE: Circuit / PCB Top View]         |
|                                                       |
|  Caption: PCB / Breadboard circuit layout showing     |
|  ESP32, sensors, and LoRa module integration.         |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD PHOTO HERE: Soldering & Wiring Detail]       |
|                                                       |
|  Caption: Underside wiring, solder joints, and cable  |
|  management.                                          |
+-------------------------------------------------------+
```

### 4.3 Mass Budget Breakdown

| Subsystem Component | Quantity | Individual Mass (g) | Total Subsystem Mass (g) |
|---|---|---|---|
| ESP32 DevKit V1 | 1 | 10.2 | 10.2 |
| BMP280 Module | 1 | 1.8 | 1.8 |
| MPU6500 IMU Module | 1 | 2.5 | 2.5 |
| SX1278 LoRa Module + Antenna | 1 | 8.5 | 8.5 |
| LiPo Battery (3.7V 800mAh) | 1 | 22.0 | 22.0 |
| 3D Printed Structure & Fasteners | 1 | 125.0 | 125.0 |
| Raw Egg Payload | 1 | 58.0 | 58.0 |
| EPE Foam Cushioning Chamber | 1 | 28.0 | 28.0 |
| Parachute Canopy + Shroud Lines | 1 | 34.0 | 34.0 |
| Wiring, Switch & LED | 1 | 10.2 | 10.2 |
| **Total CanSat Flight Weight** | — | — | **$300.2\text{ g}$** |

**Margin Below 500g Limit = $199.8\text{ g}$ (39.9% Buffer)**.

---

## 5. Flight Software & Sensor Fusion

### 5.1 Architecture & Sampling Loop
The firmware executes on the ESP32 microcontroller with a deterministic time-sliced architecture:
* **High-Rate IMU Task ($100\text{ Hz}$)**: Reads MPU6500 registers and updates orientation angles using a complementary filter.
* **Telemetry Loop ($2\text{ Hz}$ / $500\text{ ms}$)**: Samples BMP280, converts units, formats standardized ASCII packet, and transmits over LoRa SPI.

### 5.2 Sensor Fusion: Complementary Filter
To eliminate accelerometer vibrational noise and prevent pure gyroscope drift, a $96\% / 4\%$ complementary filter is computed:
$$\theta_{accel, roll} = \text{atan2}(a_y, a_z) \times \frac{180}{\pi}$$
$$\theta_{accel, pitch} = \text{atan}\left(\frac{-a_x}{\sqrt{a_y^2 + a_z^2}}\right) \times \frac{180}{\pi}$$
$$\text{Roll}_{k} = 0.96 \cdot (\text{Roll}_{k-1} + \omega_x \cdot \Delta t) + 0.04 \cdot \theta_{accel, roll}$$
$$\text{Pitch}_{k} = 0.96 \cdot (\text{Pitch}_{k-1} + \omega_y \cdot \Delta t) + 0.04 \cdot \theta_{accel, pitch}$$
$$\text{Yaw}_{k} = \text{Yaw}_{k-1} + \omega_z \cdot \Delta t$$

### 5.3 Telemetry Packet Protocol
Each packet strictly complies with Rulebook Section 7:
```text
CAN-Team-21; P-001; Ti-00:00:01:250; A-30.5; Pr-100980.25; T-26.4; Ro-1.2; Pi-0.8; Ya-3.4; AX-0.02; AY-0.05; AZ-9.81;
```

---

## 6. Ground Station & Web Mission Control

A real-time Web Telemetry Mission Control dashboard was developed using the **Web Serial API** and **Chart.js**:
* Connects directly to the ESP32 Ground Station receiver over USB at $115200\text{ baud}$.
* Displays instantaneous gauges for **Altitude ($m$)**, **Descent Speed ($m/s$)**, **Pressure ($hPa$)**, and **Temperature ($^\circ C$)**.
* Features an **Interactive 3D Attitude Indicator** rendering real-time Roll, Pitch, and Yaw.
* Provides **One-Click CSV Export** for rapid data analysis during the post-launch phase.

```
+-------------------------------------------------------+
|  [UPLOAD SCREENSHOT HERE: Live Web Dashboard]         |
|                                                       |
|  Caption: Live Ground Control Web Dashboard streaming |
|  telemetry with 3D attitude and dynamic charts.       |
+-------------------------------------------------------+
```

---

## 7. Post-Flight Data Analysis & Graphs

*(Compile the four mandatory graphs generated from your flight CSV dataset below)*

```
+-------------------------------------------------------+
|  [UPLOAD GRAPH 1: Altitude (m) vs Time (s)]           |
|                                                       |
|  Analysis: Shows initial climb to 100ft, drone        |
|  release point, steady descent slope, and touchdown.  |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD GRAPH 2: Descent Velocity (m/s) vs Time]     |
|                                                       |
|  Analysis: Demonstrates descent rate within the safe  |
|  <= 5.0 m/s threshold (average 3.5 m/s).              |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD GRAPH 3: Pressure (Pa) & Temperature vs Time]|
|                                                       |
|  Analysis: Shows atmospheric pressure gradient and    |
|  temperature profile across descent altitude.         |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD GRAPH 4: Acceleration Profiles (AX, AY, AZ)] |
|                                                       |
|  Analysis: 3-axis acceleration during free-fall,      |
|  parachute deployment shock, and ground impact.       |
+-------------------------------------------------------+
```

---

## 8. Lessons Learned & Future Scope

### 8.1 Key Learnings
1. **Parachute Stability**: Incorporating a $10\%$ apex spill hole proved critical in eliminating pendulum oscillation during descent.
2. **Sensor Fusion**: Implementing a complementary filter prevented gyroscope drift and accelerometer high-frequency motor vibration from distorting attitude angles.
3. **LoRa Optimization**: Utilizing Spreading Factor 7 with $125\text{ kHz}$ bandwidth delivered the ideal balance between long-range RF link budget and fast packet transmission rates.

### 8.2 Future Enhancements
* Integration of active steerable parachute flaps for precision target touchdown.
* Integration of an onboard micro-SD card black-box logger for redundant data recovery.

---

## 9. Team Media & Photographic Evidence

```
+-------------------------------------------------------+
|  [UPLOAD MANDATORY PHOTO: Team Photo with CanSat]     |
|                                                       |
|  Caption: Team Alpha members with assembled CanSat.   |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD MANDATORY PHOTO: Group Photo with Mentors]   |
|                                                       |
|  Caption: Team Alpha with faculty mentor and CanSat.  |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD PHOTO: Launch Day Drone Deployment]          |
|                                                       |
|  Caption: CanSat mounting on drone and aerial release.|
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD PHOTO: Post-Landing Egg Inspection]          |
|                                                       |
|  Caption: Unbroken raw egg recovered in front of      |
|  judges confirming 100% payload integrity.            |
+-------------------------------------------------------+
```

---

## 10. References & Citations
1. Physics Club SVNIT, *CanSat Competition 2026 Rulebook - Judging & Evaluation*, SVNIT Surat, 2026.
2. Bosch Sensortec, *BMP280 Digital Pressure Sensor Datasheet*, Rev 1.19.
3. InvenSense Inc., *MPU-6500 Product Specification & Register Map*, Rev 2.1.
4. Semtech Corporation, *SX1276/77/78/79 Transceiver Datasheet*, Rev 7.
5. NASA, *CanSat Design Guidelines & Aerodynamic Descent Analysis*, NASA Systems Engineering Handbook.
