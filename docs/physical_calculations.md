# 📐 CanSat 2026: Physical Aspects & Engineering Calculations
**Team**: Team Alpha (CAN-Team-07)  
**Competition**: Physics Club, SVNIT Surat — National Space Day 2026

---

## 1. Mission Profile & Constraints Overview

| Constraint / Requirement | Rulebook Limit | Our Design Value | Margin / Safety Factor |
|---|---|---|---|
| **Max Dimensions** | $21\text{ cm} (+7\text{ cm max for egg}) \times 12\text{ cm}$ | $20\text{ cm (height)} \times 10\text{ cm (dia)}$ | 33% volume margin |
| **Max Mass** | $500\text{ g } (\pm 10\%)$ | **$330\text{ g}$** | **$170\text{ g}$ (34% safety margin)** |
| **Drop Altitude** | $100\text{ ft} = 30.48\text{ m}$ (Drone drop) | $30.48\text{ m}$ | Nominal drop height |
| **Descent Rate Limit** | $\le 5.0\text{ m/s}$ | **$3.5\text{ m/s}$** | 30% below max limit (optimal points) |
| **Flight Duration** | Longer stable flight = higher points | **$8.7\text{ seconds}$** | ~43% longer than a 5 m/s drop |
| **Telemetry Rate** | $\ge 1\text{ packet/second}$ | **$2.0\text{ packets/second}$** | 100% above minimum |
| **RF Frequency & Sync** | $433\text{ MHz}$, Sync `0xA5` | $433.0\text{ MHz}$, `0xA5` | Exact match |

---

## 2. Parachute Aerodynamics & Sizing Calculation

### 2.1 Drag Force & Terminal Velocity Formula
When the CanSat is released from the drone, gravity accelerates it downwards until aerodynamic drag equals gravitational force ($F_d = F_g$):

$$m \cdot g = \frac{1}{2} \rho \cdot v^2 \cdot C_d \cdot A$$

Where:
* $m$ = Total CanSat mass with egg & parachute = $0.330\text{ kg}$
* $g$ = Acceleration due to gravity = $9.80665\text{ m/s}^2$
* $\rho$ = Air density at Surat sea level ($25^\circ\text{C}, 1013.25\text{ hPa}$) = $1.184\text{ kg/m}^3$
* $C_d$ = Drag coefficient for hemispherical parachute with spill hole = $0.75$
* $v$ = Target steady-state descent velocity = $3.5\text{ m/s}$
* $A$ = Projected surface area of canopy ($\text{m}^2$)

### 2.2 Sizing Area ($A$) and Canopy Diameter ($D$)
Rearranging for surface area:

$$A = \frac{2 \cdot m \cdot g}{\rho \cdot v^2 \cdot C_d}$$

Substituting values:

$$A = \frac{2 \times 0.330 \times 9.80665}{1.184 \times (3.5)^2 \times 0.75} = \frac{6.4724}{10.878} = 0.595\text{ m}^2$$

For a hemispherical parachute canopy ($A = \frac{\pi D^2}{4}$):

$$D = \sqrt{\frac{4 \cdot A}{\pi}} = \sqrt{\frac{4 \times 0.595}{3.14159}} = \sqrt{0.7576} \approx 0.87\text{ m} = 87\text{ cm}$$

> [!TIP]
> **Recommended Parachute Specification**:
> * **Flat Diameter**: **$90\text{ cm}$** (allowing for hem seams and 10% spill hole).
> * **Spill Hole**: Center apex hole diameter = **$9\text{ cm}$** (prevents pendulum swinging and chaotic oscillations during descent).
> * **Shroud Lines**: 8 braided nylon lines, line length = $1.2 \times D = 108\text{ cm}$ each.
> * **Canopy Material**: 30D / 40D Ripstop Nylon (lightweight, non-porous).

---

## 3. Flight Time & Trajectory

* **Drop Height**: $h = 30.48\text{ m}$ ($100\text{ ft}$)
* **Parachute Inflation Time**: $\sim 0.8\text{ s}$ ($h_{inflate} \approx 3.1\text{ m}$)
* **Steady Terminal Velocity**: $v = 3.5\text{ m/s}$
* **Descent Time**:
  $$t_{descent} = 0.8\text{ s} + \frac{30.48 - 3.1}{3.5} = 0.8 + 7.82 = 8.62\text{ s} \approx 8.7\text{ seconds}$$

At 2 packets per second, the Ground Station will receive **~17 to 20 complete telemetry packets** during the drop, easily securing full points under Section 3B (Real-Time Transmission).

---

## 4. Egg Payload Integrity & Impact Physics

### 4.1 Kinetic Energy at Impact
$$E_k = \frac{1}{2} m v^2 = \frac{1}{2} (0.330\text{ kg}) (3.5\text{ m/s})^2 = 2.02\text{ Joules}$$

### 4.2 Impact Force on the Egg
* Average egg mass: $m_{egg} \approx 0.058\text{ kg}$ ($58\text{ g}$)
* Egg crushing threshold (axial compression): $\sim 25\text{ N}$
* Cushioning: High-density EPE / Polyurethane memory foam thickness $d = 3.5\text{ cm} = 0.035\text{ m}$.

Deceleration upon ground impact with foam deformation:
$$a_{impact} = \frac{v^2}{2 \cdot d} = \frac{(3.5)^2}{2 \times 0.035} = \frac{12.25}{0.07} = 175\text{ m/s}^2 \approx 17.8\text{ g}$$

Peak Force on Egg:
$$F_{egg} = m_{egg} \times a_{impact} = 0.058\text{ kg} \times 175\text{ m/s}^2 = 10.15\text{ N}$$

$$\text{Safety Factor} = \frac{25\text{ N (Fracture limit)}}{10.15\text{ N (Actual load)}} \approx 2.46$$

> **Conclusion**: The egg will easily survive with **0 cracks (20/20 points)**.

---

## 5. Mass Budget Breakdown

| Item | Component / Material | Mass (g) |
|---|---|---|
| 1 | ESP32 DevKit V1 microcontroller | 10.2 |
| 2 | BMP180 barometric pressure/altitude sensor | 2.1 |
| 3 | MPU6050 6-DOF IMU sensor | 3.4 |
| 4 | SX1278 LoRa 433 MHz RA-02 module + spring antenna | 8.5 |
| 5 | Single-cell 3.7V 800mAh LiPo Battery | 22.0 |
| 6 | 3D Printed Chassis (PLA / PETG shell + ribs) | 115.0 |
| 7 | Egg Payload (Standard Grade A chicken egg) | 58.0 |
| 8 | EPE Foam Cushioning Chamber | 28.0 |
| 9 | Ripstop Nylon Parachute + Shroud lines | 38.0 |
| 10 | Toggle Switch, Indicator LED, Jumper wires, Screws | 15.0 |
| **TOTAL** | **All integrated flight systems** | **~300.2 g** |

**Margin below 500g limit = 199.8 g (~40% buffer)**.

---

## 6. Electrical Power Budget

| Subsystem | Operating Voltage | Active Current | Duty Cycle | Average Current |
|---|---|---|---|---|
| ESP32 DevKit (CPU 80MHz, WiFi OFF) | 3.3V | 45 mA | 100% | 45.0 mA |
| BMP180 Barometer | 3.3V | 0.8 mA | 100% | 0.8 mA |
| MPU6050 IMU | 3.3V | 3.8 mA | 100% | 3.8 mA |
| LoRa SX1278 (TX Mode @ +17dBm) | 3.3V | 95 mA | 20% (TX bursts) | 19.0 mA |
| Status LED Indicator | 3.3V | 10 mA | 100% | 10.0 mA |
| **Total System Draw** | — | — | — | **~78.6 mA** |

Using an **800 mAh LiPo battery**:
$$\text{Operating Time} = \frac{800\text{ mAh}}{78.6\text{ mA}} \approx 10.1\text{ hours}$$

The battery will provide **over 10 hours of continuous operation**, easily sustaining pre-launch checks, flight, and post-landing beaconing.\n