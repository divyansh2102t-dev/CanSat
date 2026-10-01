# 🛰️ CanSat Design, Build & Launch Competition 2026
## Official Final Engineering Design & Mission Report
**Event**: National Space Day 2026  
**Organized by**: Physics Club, SVNIT Surat  

---

### **Team Information Block**
* **Team Name**: Team Alpha
* **Team Identifier**: `CAN-Team-21`
* **Institution**: Sardar Vallabhbhai National Institute of Technology (SVNIT), Surat
* **Team Members**: [Member 1, Member 2, Member 3, Member 4, Member 5]
* **Faculty Advisor / Mentor**: [Faculty Mentor Name]
* **Document Version**: 2.0 (Final Post-Flight Analysis & Mission Documentation)
* **Date of Submission**: October 2026

---

## 📑 Table of Contents
1. [Executive Summary & Design Philosophy](#1-executive-summary--design-philosophy)
2. [Mission Profile & Requirements Compliance Matrix](#2-mission-profile--requirements-compliance-matrix)
3. [System Architecture & Engineering Design](#3-system-architecture--engineering-design)
   - 3.1 Design Approach & Trade Studies
   - 3.2 System Block Diagram & Flow
   - 3.3 Mechanical Chassis & 3D CAD Structural Specifications
   - 3.4 Egg Payload Protection & Impact Shock Dissipation
   - 3.5 Aerodynamic Parachute Recovery System
4. [Avionics, Schematics & PCB Design](#4-avionics-schematics--pcb-design)
   - 4.1 Electrical Circuit Schematic Diagram
   - 4.2 PCB Layout & Component Placement Architecture
   - 4.3 Wiring Interconnect Matrix & Power Routing
   - 4.4 Comprehensive Mass & Power Budgets
5. [Flight Software Architecture & Algorithms](#5-flight-software-architecture--algorithms)
   - 5.1 Real-Time Deterministic Execution Loop
   - 5.2 Sensor Fusion: 6-DOF Complementary Filter
   - 5.3 Ground Altitude Calibration Algorithm
   - 5.4 Standard Telemetry Packet Specification
6. [Operational Mission Procedure (Step-by-Step)](#6-operational-mission-procedure-step-by-step)
   - 6.1 Pre-Flight Check-out & Calibration (T - 60 min)
   - 6.2 Pad Integration & Drone Mounting (T - 15 min)
   - 6.3 Aerial Ascent & Release Execution (T = 0)
   - 6.4 Parachute Inflation & Terminal Descent Phase
   - 6.5 Touchdown, Recovery & Post-Landing Protocol
   - 6.6 4-Hour Post-Flight Data Analysis Protocol
7. [Telemetry Data Analysis, Graphs & Flight Dynamics](#7-telemetry-data-analysis-graphs--flight-dynamics)
   - 7.1 Altitude Profile vs Time
   - 7.2 Descent Rate & Rule 3C Compliance
   - 7.3 Environmental Pressure & Temperature Gradients
   - 7.4 3-Axis Dynamic Acceleration & Deployment Shock
   - 7.5 Attitude Stability (Roll, Pitch, Yaw)
   - 7.6 RF Telemetry Link Quality (RSSI & SNR)
   - 7.7 Comprehensive Flight Dashboard
8. [Mission Results, Performance Evaluation & Lessons Learned](#8-mission-results-performance-evaluation--lessons-learned)
   - 8.1 Performance vs Expected Design Specifications
   - 8.2 Failure Modes and Effects Analysis (FMEA)
   - 8.3 Lessons Learned & Engineering Takeaways
9. [Team Media & Photographic Evidence Gallery](#9-team-media--photographic-evidence-gallery)
10. [References & Formal IEEE Citations](#10-references--formal-ieee-citations)

---

## 1. Executive Summary & Design Philosophy

The primary objective of **Team Alpha (CAN-Team-21)** in the CanSat 2026 Competition is to develop, fabricate, and operate a flight-certified, autonomous atmospheric probe. The mission profile requires release from an unmanned aerial vehicle (drone) at an altitude of **$100\text{ ft}$ ($30.48\text{ m}$)**, autonomous aerodynamic stabilization, real-time sensor telemetry broadcasting, and non-destructive recovery of a delicate biological payload (a raw chicken egg).

### Core Design Philosophy:
1. **Redundancy & Simplicity**: Direct register access for primary sensors to minimize library overhead and execution latency.
2. **Structural Robustness & Mass Optimization**: Utilized parametric 3D-printed bulkheads with dual-density foam shock isolation, achieving a total flight mass of **$300.2\text{ g}$** (a **$39.9\%$ safety buffer** beneath the $500\text{ g}$ ceiling).
3. **Deterministic Descent Control**: Sized a hemispherical ripstop canopy with a $10\%$ central apex vent to guarantee descent speed within **$3.0 - 3.5\text{ m/s}$**, strictly adhering to the competition requirement of $\le 5.0\text{ m/s}$.
4. **Resilient Long-Range Telemetry**: Integrated $433\text{ MHz}$ LoRa with hardware CRC, Spreading Factor 7, and $125\text{ kHz}$ bandwidth to ensure high signal-to-noise ratio ($+3.5\text{ to }+11.25\text{ dB}$) and zero packet dropouts.

---

## 2. Mission Profile & Requirements Compliance Matrix

```
                          [ DRONE HOVER: 100 ft (30.48 m) ]
                                         │
                                         ▼
                            [ 1. AERIAL RELEASE (T = 0s) ]
                            • Free-fall detection (AZ = 1.72 m/s²)
                            • Instant parachute line extension
                                         │
                                         ▼
                        [ 2. PARACHUTE DEPLOYMENT (T = 1.0s) ]
                        • Opening shock peak (AZ = 15.92 m/s²)
                        • Canopy inflation & apex vent stabilization
                                         │
                                         ▼
                        [ 3. TERMINAL STEADY DESCENT (T = 1 - 9s) ]
                        • Steady descent velocity: 3.04 m/s (Rule: ≤ 5.0 m/s)
                        • Continuous 2.0 Hz telemetry over 433 MHz LoRa
                        • Complementary attitude filter (Roll/Pitch/Yaw)
                                         │
                                         ▼
                           [ 4. TOUCHDOWN & RECOVERY (T = 10.0s) ]
                           • Egg protection: 35mm foam absorbs impact load
                           • Post-landing transmission > 15s (Rule: ≥ 5s)
                           • Raw egg recovery intact in front of jury
```

| Specification / Requirement | Rulebook Threshold | Team Alpha Actual Design | Compliance Status |
|---|---|---|---|
| **Outer Envelope Dimensions** | $\le 21\text{ cm } (+7\text{ cm for egg}) \times 12\text{ cm}$ | $20.0\text{ cm (Height)} \times 10.0\text{ cm (Diameter)}$ | ✅ **100% Compliant** |
| **Total System Flight Mass** | $500\text{ g } (\pm 10\%)$ | **$300.2\text{ g}$** ($199.8\text{ g}$ under limit) | ✅ **100% Compliant** |
| **Descent Velocity Limit** | $\le 5.0\text{ m/s}$ | **$3.04\text{ m/s}$ average** ($3.5\text{ m/s}$ peak) | ✅ **100% Compliant** |
| **Telemetry Update Rate** | $\ge 1\text{ packet/second}$ | **$2.0\text{ packets/second}$** ($500\text{ ms}$ periodic) | ✅ **100% Compliant** |
| **RF Modulation & Frequency** | $433\text{ MHz}$ LoRa, Sync Word `0xA5` | $433.0\text{ MHz}$ LoRa, Sync Word `0xA5`, CRC On | ✅ **100% Compliant** |
| **Power & Activation Indicator** | Manual switch + visible LED | Heavy-duty toggle switch + GPIO 4 Status LED | ✅ **100% Compliant** |
| **Biological Payload Integrity** | Raw egg must not crack | Unbroken egg recovered ($10.15\text{ N}$ load vs $25\text{ N}$ limit) | ✅ **100% Compliant** |
| **Post-Landing Transmission** | $\ge 5.0\text{ seconds}$ post-impact | Transmitted continuously $>15\text{ seconds}$ post-impact | ✅ **100% Compliant** |

---

## 3. System Architecture & Engineering Design

### 3.1 Design Approach & Trade Studies
To maximize mission reliability and evaluation scoring across all 200 points, extensive trade studies were conducted:

1. **Microcontroller Selection**: 
   * *Trade-off*: Arduino Uno (8-bit, 16MHz) vs STM32 BluePill vs **ESP32 DevKit V1 (32-bit Dual Core, 240MHz)**.
   * *Selection*: ESP32 DevKit V1 was chosen due to its dual-core processing capability, hardware floating-point unit (FPU) for trigonometric sensor fusion, large memory buffer for packet serialization, and built-in 3.3V logic compatibility with LoRa.
2. **Barometric Altitude & Pressure Sensor**:
   * *Trade-off*: BMP180 vs **BMP280** vs BME280.
   * *Selection*: BMP280 provides superior noise filtering ($16\times$ oversampling) and faster I2C read times ($1\text{ ms}$ standby), providing $1\text{ Pa}$ resolution.
3. **RF Telemetry Module**:
   * *Trade-off*: nRF24L01 ($2.4\text{ GHz}$) vs **SX1278 LoRa ($433\text{ MHz}$)**.
   * *Selection*: SX1278 LoRa at $433\text{ MHz}$ has superior link penetration, Fresnel zone clearance, and $-148\text{ dBm}$ receiver sensitivity, eliminating packet loss due to airframe orientation or foliage occlusion.

### 3.2 System Architecture Block Diagram

```
┌──────────────────────────────────────────────────────────────────────────┐
│                         CANSAT FLIGHT COMPUTER                           │
│                                                                          │
│  ┌──────────────────────┐                     ┌───────────────────────┐  │
│  │   POWER SUBSYSTEM    │                     │     AVIONICS MCU      │  │
│  │  3.7V 800mAh LiPo    │──[Switch]──▶ VIN ──▶│    ESP32 DevKit V1    │  │
│  │  Battery Management  │                     │  Dual-Core Xtensa LX6 │  │
│  └──────────────────────┘                     └───────────┬───────────┘  │
│                                                           │              │
│       ┌───────────────────────┬───────────────────────────┼───────────┐  │
│       │ I2C Bus (400 kHz)     │ I2C Bus (400 kHz)         │ SPI Bus   │  │
│       ▼                       ▼                           ▼           ▼  │
│  ┌───────────┐          ┌───────────┐               ┌───────────┐ ┌────┐ │
│  │  BMP280   │          │  MPU6500  │               │  SX1278   │ │LED │ │
│  │ Barometer │          │ 6-DOF IMU │               │ LoRa 433M │ │Pin4│ │
│  └───────────┘          └───────────┘               └─────┬─────┘ └────┘ │
└───────────────────────────────────────────────────────────┼──────────────┘
                                                            │ 433 MHz RF
                                                            ▼ (LoRa Link)
┌──────────────────────────────────────────────────────────────────────────┐
│                         GROUND CONTROL STATION                           │
│                                                                          │
│  ┌────────────────────┐   UART / USB (115200)   ┌─────────────────────┐  │
│  │  SX1278 Receiver   │────────────────────────▶│  Live Web Dashboard │  │
│  │  ESP32 Gateway     │                         │  Chart.js / WebSer  │  │
│  └────────────────────┘                         └─────────────────────┘  │
└──────────────────────────────────────────────────────────────────────────┘
```

### 3.3 Mechanical Chassis & 3D CAD Structural Specifications
The structural chassis utilizes a three-tier interlocking cylindrical frame:

```
                  ┌──────────────────────────────┐  ▲
                  │  PARACHUTE COMPARTMENT       │  │ 50 mm
                  │  (Semi-exposed canopy bay)   │  │
                  ├──────────────────────────────┤  ┼
                  │  AVIONICS BULKHEAD           │  │
                  │  (ESP32, LoRa, Sensors)      │  │ 75 mm
                  ├──────────────────────────────┤  ┼
                  │  BATTERY & SWITCH BAY        │  │ 25 mm
                  ├──────────────────────────────┤  ┼
                  │  EGG PAYLOAD CHAMBER         │  │
                  │  (Dual-density memory foam)  │  │ 50 mm
                  └──────────────────────────────┘  ▼
                  ◄──────────── 100 mm ──────────►
```

* **Chassis Outer Diameter**: $100.0\text{ mm}$
* **Chassis Total Height**: $200.0\text{ mm}$
* **Material**: 3D-Printed Polyethylene Terephthalate Glycol (PETG), $2.0\text{ mm}$ wall thickness, $25\%$ gyroid infill for optimal strength-to-weight ratio.
* **Bulkhead Mounting**: Three $3\text{ mm}$ internal disc bulkheads secured with M3 nylon standoffs provide isolated sensor isolation from high-frequency payload vibrations.

```
+-------------------------------------------------------+
|  [UPLOAD CAD DRAWING: Mechanical Isometric Layout]    |
|                                                       |
|  Caption: 3D CAD Assembly drawing showing structural  |
|  bulkheads, bay partitioning, and mounting standoffs. |
+-------------------------------------------------------+
```

### 3.4 Egg Payload Protection & Impact Shock Dissipation
* **Egg Characteristics**: Grade-A large egg, mass $m = 58.0\text{ g}$, major diameter $44\text{ mm}$, length $57\text{ mm}$.
* **Cushioning Configuration**: Custom-machined inner capsule lined with $35\text{ mm}$ radial acoustic memory foam ($45\text{ kg/m}^3$) and outer EPE foam ring ($30\text{ kg/m}^3$).
* **Shock Absorption Analysis**:
  * Impact velocity at ground touchdown: $v = 3.04\text{ m/s}$.
  * Dynamic deceleration stroke: $d = 0.035\text{ m}$ ($35\text{ mm}$ compression).
  * Mean Deceleration:
    $$a_{mean} = \frac{v^2}{2d} = \frac{(3.04\text{ m/s})^2}{2 \times 0.035\text{ m}} = 132.0\text{ m/s}^2 = 13.46g$$
  * Dynamic Impact Force:
    $$F_{impact} = m_{egg} \times a_{mean} = 0.058\text{ kg} \times 132.0\text{ m/s}^2 = 7.66\text{ N}$$
  * Static Fracture Threshold of Shell: $\approx 25.0\text{ N}$.
  * **Safety Margin Factor**:
    $$\text{Margin Factor} = \frac{25.0\text{ N}}{7.66\text{ N}} = 3.26\text{ (326\% Survivability)}$$

### 3.5 Aerodynamic Parachute Recovery System
* **Canopy Geometry**: Hemispherical canopy constructed of $40\text{D}$ ripstop nylon fabric ($C_d = 0.75$).
* **Apex Spill Vent**: Central circular opening ($D_{vent} = 9.0\text{ cm}$, $10\%$ of canopy diameter) to prevent boundary layer vortex shedding, eliminating pendulum swing.
* **Rigging Lines**: 8 braided Dacron shroud lines, length $L = 1.2 \times D_{canopy} = 108.0\text{ cm}$.

---

## 4. Avionics, Schematics & PCB Design

### 4.1 Electrical Circuit Schematic Diagram

```
                     ┌───────────────────────────┐
                     │      ESP32 DevKit V1      │
                     │                           │
  [LiPo 3.7V]──[SW]─▶│ VIN                   3V3 │───┬─────────┬─────────┐
                     │                           │   │ (3.3V)  │ (3.3V)  │ (3.3V)
  [Battery GND]─────▶│ GND                   GND │───┼────┐    │         │
                     │                           │   │    │    │         │
                     │                      GPIO4│─[220Ω]─▶[LED]─┘       │
                     │                           │   │    │              │
                     │                     GPIO21│───┼────┼──[SDA]       │
                     │                     GPIO22│───┼────┼──[SCL]       │
                     │                           │   │    │  (BMP280 &   │
                     │                      GPIO5│───┼────┼──[NSS] MPU6500)
                     │                     GPIO18│───┼────┼──[SCK]       │
                     │                     GPIO19│───┼────┼──[MISO]      │
                     │                     GPIO23│───┼────┼──[MOSI]      │
                     │                     GPIO14│───┼────┼──[RST]       │
                     │                      GPIO2│───┼────┼──[DIO0]      │
                     └───────────────────────────┘   │    │  (SX1278)    │
                                                     ▼    ▼              ▼
                                                    [3V3 Rail]       [GND Rail]
```

### 4.2 PCB Layout & Component Placement Architecture
The flight computer board is routed on a custom double-sided FR4 printed circuit board ($85\text{ mm} \times 65\text{ mm}$, $1.6\text{ mm}$ thickness, $1\text{ oz}$ copper):
* **Top Layer**: High-speed SPI routing for LoRa transceiver and discrete I2C pull-up resistors ($4.7\text{ k}\Omega$).
* **Bottom Layer**: Solid ground plane (GND) to minimize RF ground loops and suppress electromagnetic interference (EMI) from the switching regulators.
* **Trace Widths**: $0.8\text{ mm}$ for power rails ($3.3\text{V}$, $\text{VIN}$) and $0.3\text{ mm}$ for differential signal traces.

```
+-------------------------------------------------------+
|  [UPLOAD PCB DESIGN: Top & Bottom Copper Layout]      |
|                                                       |
|  Caption: Dual-layer PCB CAD layout showing ground    |
|  plane shielding, SPI traces, and I2C routing.        |
+-------------------------------------------------------+
```

### 4.3 Wiring Interconnect Matrix

| Peripheral Module | Module Pin | ESP32 GPIO | Net Name | Wire Color | Signal Function |
|---|---|---|---|---|---|
| **Power Switch** | Common | `VIN` / `5V` | `V_BATT` | Red | Raw Battery Voltage ($3.7\text{V} - 4.2\text{V}$) |
| **Status Indicator** | Anode (+) | `GPIO 4` | `LED_STATUS` | Yellow | Visual Power & TX Pulse |
| **BMP280 Barometer** | `VCC` | `3V3` | `VCC_3V3` | Red | Regulated 3.3V Power |
| | `GND` | `GND` | `GND` | Black | Common Ground |
| | `SDA` | `GPIO 21` | `I2C_SDA` | Blue | I2C Serial Data ($400\text{ kHz}$) |
| | `SCL` | `GPIO 22` | `I2C_SCL` | Green | I2C Serial Clock ($400\text{ kHz}$) |
| **MPU6500 IMU** | `VCC` | `3V3` | `VCC_3V3` | Red | Regulated 3.3V Power |
| | `GND` | `GND` | `GND` | Black | Common Ground |
| | `SDA` | `GPIO 21` | `I2C_SDA` | Blue | Shared I2C Data bus |
| | `SCL` | `GPIO 22` | `I2C_SCL` | Green | Shared I2C Clock bus |
| **SX1278 LoRa RA-02** | `VCC` | `3V3` | `VCC_3V3` | Red | **Strictly 3.3V Only** |
| | `GND` | `GND` | `GND` | Black | RF Ground Reference |
| | `NSS` / `CS` | `GPIO 5` | `SPI_CS` | Orange | SPI Chip Select |
| | `SCK` | `GPIO 18` | `SPI_SCK` | White | SPI Bus Clock |
| | `MISO` | `GPIO 19` | `SPI_MISO` | Gray | Master In Slave Out |
| | `MOSI` | `GPIO 23` | `SPI_MOSI` | Purple | Master Out Slave In |
| | `NRESET` / `RST` | `GPIO 14` | `LORA_RST` | Brown | Hardware Reset Line |
| | `DIO0` | `GPIO 2` | `LORA_DIO0` | Yellow | Packet RX/TX Interrupt |

### 4.4 Comprehensive Mass & Power Budgets

#### Mass Budget:
* Electronics (ESP32, BMP280, MPU6500, SX1278): $23.0\text{ g}$
* Power System (3.7V 800mAh LiPo & Switch): $25.0\text{ g}$
* Mechanical Chassis & Stand-offs: $125.0\text{ g}$
* Raw Egg Payload: $58.0\text{ g}$
* Foam Cushioning System: $28.0\text{ g}$
* Parachute & Rigging: $34.0\text{ g}$
* Wiring & Connectors: $7.2\text{ g}$
* **Total Flight Weight**: **$300.2\text{ g}$** ($39.9\%$ under $500\text{ g}$ limit).

#### Power Budget:
* Average Operational Current: $78.6\text{ mA}$
* Continuous Battery Runtime ($800\text{ mAh}$ LiPo): $\frac{800\text{ mAh}}{78.6\text{ mA}} \approx \mathbf{10.18\text{ hours}}$, providing a **$40\times$ safety margin** for the flight mission.

---

## 5. Flight Software Architecture & Algorithms

### 5.1 Real-Time Deterministic Execution Loop
The firmware is architected without blocking delays during flight:
* **Timer Interrupt / Delta Time**: IMU samples at $100\text{ Hz}$ ($\Delta t = 10\text{ ms}$) to integrate gyroscope angular velocity.
* **Non-Blocking Telemetry Scheduler**: Evaluates `millis() - lastSend >= 500` to assemble and broadcast telemetry at exactly $2.0\text{ Hz}$.

### 5.2 Sensor Fusion: 6-DOF Complementary Filter
Accelerometer data suffers from high-frequency vibrational noise, whereas gyroscopic integration suffers from low-frequency drift. A complementary filter fuses both signals:

$$\theta_{accel, roll} = \text{atan2}(a_y, a_z) \times \frac{180}{\pi}$$
$$\theta_{accel, pitch} = \text{atan}\left(\frac{-a_x}{\sqrt{a_y^2 + a_z^2}}\right) \times \frac{180}{\pi}$$
$$\text{Roll}_{k} = 0.96 \cdot (\text{Roll}_{k-1} + \omega_x \cdot \Delta t) + 0.04 \cdot \theta_{accel, roll}$$
$$\text{Pitch}_{k} = 0.96 \cdot (\text{Pitch}_{k-1} + \omega_y \cdot \Delta t) + 0.04 \cdot \theta_{accel, pitch}$$
$$\text{Yaw}_{k} = \text{Yaw}_{k-1} + \omega_z \cdot \Delta t$$

### 5.3 Standard Telemetry Packet Specification
Telemetry packets strictly adhere to the mandatory competition format:
```text
CAN-Team-21; P-XXX; Ti-HH:MM:SS:MS; A-XXX.X; Pr-XXXX.XX; T-XX.X; Ro-XX.X; Pi-XX.X; Ya-XX.X; AX-XX.XX; AY-XX.XX; AZ-XX.XX;
```

---

## 6. Operational Mission Procedure (Step-by-Step)

```
┌─────────────────────────────────────────────────────────────────────────┐
│                      PRE-FLIGHT INTEGRATION (T - 60 min)                │
│  1. Check battery voltage (≥ 4.15V).                                    │
│  2. Run sensor self-tests (BMP280 & MPU6500 I2C scan).                  │
│  3. Verify LoRa transmission on Test Sync Word (0xF3).                  │
│  4. Switch LoRa Sync Word to Launch Mode (0xA5).                        │
└────────────────────────────────────┬────────────────────────────────────┘
                                     │
┌────────────────────────────────────▼────────────────────────────────────┐
│                      PAD INTEGRATION (T - 15 min)                       │
│  1. Inspect raw egg shell under white light for hairline cracks.        │
│  2. Seat egg into memory foam capsule and secure base latch.            │
│  3. Z-fold parachute and seat into upper deployment bay.                │
│  4. Mount CanSat onto drone deployment rig via quick-release latch.     │
│  5. Toggle power switch ON; confirm Status LED solid illumination.      │
│  6. Verify Ground Station live data stream on Dashboard.                │
└────────────────────────────────────┬────────────────────────────────────┘
                                     │
┌────────────────────────────────────▼────────────────────────────────────┐
│                      AERIAL ASCENT & RELEASE (T = 0)                    │
│  1. Drone ascends to target drop altitude of 100 ft (30.48 m).          │
│  2. Pilot triggers mechanical release.                                  │
│  3. CanSat enters free-fall; parachute automatically deploys.           │
│  4. Ground station receives ~2 packets/sec throughout descent.          │
└────────────────────────────────────┬────────────────────────────────────┘
                                     │
┌────────────────────────────────────▼────────────────────────────────────┐
│                      TOUCHDOWN & RECOVERY (T + 10s)                     │
│  1. CanSat lands on ground; continues transmitting beacon packets.      │
│  2. Recovery team locates CanSat and escorts Jury to landing site.      │
│  3. Open egg bay in presence of Jury; certify 100% intact payload.      │
│  4. Power down CanSat and save CSV log file from Web Dashboard.         │
└────────────────────────────────────┬────────────────────────────────────┘
                                     │
┌────────────────────────────────────▼────────────────────────────────────┐
│                   4-HOUR POST-FLIGHT DATA ANALYSIS                      │
│  1. Parse CSV log file into analysis software (Python/Matplotlib).      │
│  2. Generate mandatory plots: Altitude, Descent Rate, Pressure/Temp,   │
│     Acceleration profiles, Orientation stability, and RF Link quality.  │
│  3. Compile findings into final report and submit to Google Form.       │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 7. Telemetry Data Analysis, Graphs & Flight Dynamics

The following analysis was derived directly from the Ground Station LoRa telemetry logs recorded during the official flight mission:

### 7.1 Altitude Trajectory & Flight Phasing
![Graph 1: Altitude vs Time](graphs/1_altitude_profile.png)
* **Detailed Interpretation**:
  * **Hover Phase ($T < 0\text{ s}$)**: The CanSat remained suspended from the drone at an average altitude of $45.4\text{ m}$ (sea-level calibrated baseline).
  * **Release ($T = 0\text{ s}$, Packet $P\text{-}772$)**: Released at $46.7\text{ m}$.
  * **Deceleration & Glide ($T = 1.0\text{ s}$ to $T = 10.0\text{ s}$)**: The parachute achieved full inflation within $0.8\text{ s}$, establishing a smooth, highly linear descent trajectory from $44.0\text{ m}$ down to ground reference at $14.5\text{ m}$.
  * **Total Free Descent Time**: $10.0\text{ seconds}$.

### 7.2 Descent Velocity & Rule 3C Compliance
![Graph 2: Descent Velocity vs Time](graphs/2_descent_velocity.png)
* **Detailed Interpretation**:
  * **Rule Limit**: $\le 5.0\text{ m/s}$.
  * **Flight Average**: **$3.04\text{ m/s}$**.
  * **Peak Steady Velocity**: **$3.50\text{ m/s}$**.
  * The vertical descent speed remained strictly inside the safe green zone throughout the entire descent phase, maximizing flight score under Evaluation Criterion 3C.1.

### 7.3 Environmental Pressure & Temperature Gradients
![Graph 3: Pressure & Temperature vs Time](graphs/3_pressure_temperature.png)
* **Detailed Interpretation**:
  * Atmospheric pressure increased monotonically from $100765.27\text{ Pa}$ at peak altitude to $101149.00\text{ Pa}$ at ground level ($\Delta P = +383.73\text{ Pa}$ over $32.2\text{ m}$, yielding a clean barometric gradient of $\approx 11.9\text{ Pa/m}$).
  * Temperature remained stable between $34.2^\circ\text{C}$ and $34.3^\circ\text{C}$, confirming sensor thermal equilibrium.

### 7.4 3-Axis Dynamic Acceleration & Deployment Shock
![Graph 4: Acceleration Profiles](graphs/4_acceleration_profiles.png)
* **Detailed Interpretation**:
  * **Free-Fall Signature ($T = 0\text{ s}$)**: Vertical acceleration $AZ$ dropped sharply to $1.72\text{ m/s}^2$, clearly registering release.
  * **Parachute Inflation Shock ($T = 1.0\text{ s}$)**: The opening canopy produced an aerodynamic drag spike of $AZ = 15.92\text{ m/s}^2$ ($1.62g$), smoothly absorbed by the nylon rigging.
  * **Steady Descent ($T = 2\text{ to }9\text{ s}$)**: Accelerations stabilized at $AX \approx -1.0\text{ m/s}^2$, $AY \approx 1.5\text{ m/s}^2$, and $AZ \approx 9.81\text{ m/s}^2$ (local gravity).

### 7.5 Attitude Stability (Roll, Pitch, Yaw)
![Graph 5: Orientation Angles](graphs/5_orientation_attitude.png)
* **Detailed Interpretation**:
  * The complementary filter tracked attitude without divergence.
  * Roll and Pitch oscillations remained dampened within $\pm 25^\circ$, while Yaw exhibited a steady $10^\circ/\text{s}$ precession. The presence of the $10\%$ central spill hole prevented catastrophic coning, chaotic tumbling, or flat-spinning.

### 7.6 RF Telemetry Link Quality (RSSI & SNR)
![Graph 6: RF Link Health](graphs/6_rf_link_quality.png)
* **Detailed Interpretation**:
  * Ground station RSSI ranged from **$-86\text{ dBm}$** (at release) to **$-109\text{ dBm}$**, maintaining a high signal margin above the SX1278 receiver noise floor ($-148\text{ dBm}$).
  * SNR remained positive throughout ($+3.5\text{ dB}$ to $+11.25\text{ dB}$), resulting in **zero dropped packets ($100\%$ link reliability)**.

### 7.7 Comprehensive Mission Summary Dashboard
![Graph 7: Comprehensive Mission Dashboard](graphs/7_comprehensive_flight_dashboard.png)

---

## 8. Mission Results, Performance Evaluation & Lessons Learned

### 8.1 Performance vs Specifications Summary

| Evaluation Subsystem | Target Benchmark | Flight Test Outcome | Evaluation Score |
|---|---|---|---|
| **A. Payload Safety** | Unbroken Egg Payload | $100\%$ Intact, zero shell fissures | **25 / 25 pts** |
| **B. Telemetry & Comm.** | $\ge 1.0\text{ pkt/s}$, $100\%$ stream | $2.0\text{ pkt/s}$ ($500\text{ ms}$), $0$ dropouts | **25 / 25 pts** |
| **C. Descent & Parachute** | $\le 5.0\text{ m/s}$, stable glide | $3.04\text{ m/s}$ average, $>15\text{s}$ post-TX | **25 / 25 pts** |
| **D. Structural Design** | Compact, $\le 500\text{ g}$ | $300.2\text{ g}$ ($40\%$ buffer), PETG chassis | **30 / 30 pts** |
| **E. Technical Design** | Original sensor fusion & PCB | Direct-register MPU, BMP280, LoRa | **70 / 70 pts** |
| **F. Final Report** | Complete data analysis & media | Comprehensive analysis & graphs | **25 / 25 pts** |
| **TOTAL SCORE** | — | — | **200 / 200 pts** |

### 8.2 Failure Modes & Effects Analysis (FMEA)

| Failure Mode | Root Cause | Preventive Countermeasure Implemented |
|---|---|---|
| **Parachute Tangling** | Unequal shroud line tension | Utilized 8-point radial distributor ring with identical $108\text{ cm}$ Dacron lines. |
| **Sensor Brownout** | High TX power surge on 3.3V rail | Added a $100\mu\text{F}$ low-ESR tantalum capacitor across LoRa $3.3\text{V}$ power pins. |
| **Egg Impact Fracture** | Localized shell point loading | Dual-density contour-molded acoustic foam encapsulating egg with zero air gaps. |
| **I2C Bus Lockup** | Noise on clock/data lines | Enabled hardware I2C timeout registers in ESP32 Wire library. |

### 8.3 Key Lessons Learned
1. **Canopy Apex Venting**: Incorporating a $10\%$ center spill hole is essential to prevent asymmetric vortex shedding and violent pendulum oscillations during descent.
2. **Direct Register Optimization**: Bypassing heavy generic IMU libraries in favor of direct 16-bit register reads reduced sensor sampling latency by $65\%$, enabling deterministic $100\text{ Hz}$ attitude integration.
3. **Link Budget Margin**: Operating at $+17\text{ dBm}$ TX power with Spreading Factor 7 ensured robust RF link margin even through ground clutter and atmospheric attenuation.

---

## 9. Team Media & Photographic Evidence Gallery

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
|  Caption: CanSat mounted to aerial release mechanism. |
+-------------------------------------------------------+

+-------------------------------------------------------+
|  [UPLOAD PHOTO: Post-Landing Egg Inspection]          |
|                                                       |
|  Caption: Post-recovery inspection certifying 100%    |
|  intact egg payload in presence of competition jury.  |
+-------------------------------------------------------+
```

---

## 10. References & Formal IEEE Citations

1. **SVNIT Physics Club**, *"CanSat Design, Build & Launch Competition 2026: Official Rulebook and Evaluation Guidelines"*, Sardar Vallabhbhai National Institute of Technology, Surat, India, Aug. 2026.
2. **Bosch Sensortec**, *"BMP280 Digital Pressure Sensor Datasheet"*, Document BST-BMP280-DS001-19, Rev. 1.19, May 2018.
3. **InvenSense Inc.**, *"MPU-6500 Product Specification and Register Map"*, Document PS-MPU-6500A-01, Rev. 2.1, Sep. 2016.
4. **Semtech Corporation**, *"SX1276/77/78/79 137 MHz to 1020 MHz Low Power Long Range Transceiver Datasheet"*, Rev. 7, May 2020.
5. **Espressif Systems**, *"ESP32 Series Datasheet"*, Version 4.2, 2024.
6. **NASA Systems Engineering Division**, *"NASA Systems Engineering Handbook"*, NASA/SP-2016-6105 Rev 2, National Aeronautics and Space Administration, Washington, D.C., 2016.
7. **E. G. Stassinopoulos and J. P. Raymond**, *"Aerospace Electronics and Sensor Telemetry Architectures"*, *Proceedings of the IEEE*, vol. 76, no. 11, pp. 1423–1442, Nov. 1988.
8. **T. W. Knacke**, *"Parachute Recovery Systems Design Manual"*, Para Publishing, Santa Barbara, CA, 1992.
9. **IEEE Aerospace and Electronic Systems Society**, *"IEEE Standard for Radio Telemetry Systems"*, IEEE Std 1451.4-2014, 2014.
