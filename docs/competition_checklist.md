# 📋 CanSat 2026: Pre-Launch, Flight & Recovery Checklist
**Team**: Team Alpha (CAN-Team-07)

---

## Phase 1: Bench Check (Night Before Launch)
- [ ] **Firmware Verification**: Verify `ACTIVE_SYNC_WORD` in `flight_computer.ino` is set to `0xA5` for launch day.
- [ ] **Sensor Tests**: Run `test_bmp180.ino` and `test_mpu6050.ino` to verify zero drift.
- [ ] **LoRa Range Test**: Place CanSat 30m away, confirm packets stream at -60 to -80 dBm RSSI.
- [ ] **Battery Charge**: Ensure LiPo is charged to 4.2V (100%).
- [ ] **Parachute Inspection**: Ensure 8 shroud lines are untangled, center spill hole is unobstructed.
- [ ] **Egg Cushioning**: Test fit raw egg with top and bottom foam cups.

---

## Phase 2: Launch Site Preparation (15 Mins Before Drop)
- [ ] Turn ON Ground Station ESP32 and open Web Dashboard (`dashboard/index.html` in Chrome).
- [ ] Click **Connect Ground Station** and select the COM port.
- [ ] Verify clean baseline data reception.
- [ ] Install fresh raw chicken egg inside the central foam capsule.
- [ ] Fold parachute using the Z-fold method (semi-exposed on top per Rule 8).
- [ ] Turn ON CanSat manual toggle switch on ground level.
- [ ] Confirm **Status LED lights up immediately**.
- [ ] Confirm Web Dashboard shows:
  - Altitude: $0.0\text{ m} (\pm 0.2\text{ m})$
  - Packet number incrementing at $2\text{ Hz}$.

---

## Phase 3: Drone Ascent & Release
- [ ] Drone ascends with CanSat attached.
- [ ] Confirm Web Dashboard shows ascending altitude up to $\sim 30.5\text{ m}$ ($100\text{ ft}$).
- [ ] Drone releases CanSat.
- [ ] Verify instant parachute deployment (semi-exposed ejection).
- [ ] Monitor descent speed (should stay between $3.0\text{ m/s}$ and $4.0\text{ m/s}$).

---

## Phase 4: Touchdown & Recovery
- [ ] Confirm telemetry continues transmitting for at least 5 seconds post-impact (Rule 3C.3).
- [ ] Click **Export CSV** on the Web Dashboard to save the full flight telemetry dataset.
- [ ] Retrieve CanSat with Judges.
- [ ] Open egg chamber in front of Judges: Verify unbroken egg (**20/20 points**).
- [ ] Proceed to the 4-hour Data Analysis session with the exported CSV.\n