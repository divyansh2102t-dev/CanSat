/**
 * ============================================================================
 * 🛰️ CanSat 2026 - Main Flight Computer Firmware (Transmitter)
 * Team Name: Team Alpha
 * Team ID: CAN-Team-07
 * Target Board: ESP32 DevKit V1
 * Sensors: BMP180 / BMP280 (I2C), MPU6050 6-DOF IMU (I2C)
 * RF Module: SX1278 LoRa 433 MHz (SPI)
 * ============================================================================
 *
 * PACKET FORMAT SPECIFICATION (Rulebook Section 7):
 * CAN-Team-07; P-XXX; Ti-HH:MM:SS:MS; A-XXX.X; Pr-XXXX.XX; T-XX.X; Ro-XX.X; Pi-XX.X; Ya-XX.X; AX-XX.XX; AY-XX.XX; AZ-XX.XX;
 *
 * RULES COMPLIANCE:
 * - Launch Sync Word: 0xA5 (Testing Sync Word: 0xF3)
 * - Frequency: 433.0 MHz
 * - Transmission Rate: ~2 Packets / sec (>= 1 pkt/sec rule)
 * - Automatic transmission begins on boot
 * - Altitude baseline calibration at ground floor (A = 0.0m)
 * - Status LED indicator on GPIO 4
 * ============================================================================
 */

#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BMP085.h>  // Supports BMP180 & BMP085
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ======================== CONFIGURATION ========================
const String TEAM_ID = "CAN-Team-07";

// LoRa Sync Words: Use 0xA5 for Official Launch, 0xF3 for Pre-launch Testing
#define LORA_SYNC_WORD_LAUNCH  0xA5
#define LORA_SYNC_WORD_TEST    0xF3
#define ACTIVE_SYNC_WORD       LORA_SYNC_WORD_LAUNCH

#define LORA_FREQUENCY         433E6 // 433 MHz

// Pin Definitions for ESP32 DevKit V1
#define PIN_LED_STATUS         4     // Mandatory Power/TX Indicator LED
#define PIN_I2C_SDA            21    // I2C SDA (BMP + MPU)
#define PIN_I2C_SCL            22    // I2C SCL (BMP + MPU)

// LoRa SX1278 SPI Pins
#define PIN_LORA_SS            5     // NSS / CS
#define PIN_LORA_RST           14    // NRESET
#define PIN_LORA_DIO0          2     // DIO0 Interrupt

// Sea level baseline pressure in Pa (standard reference: 101325 Pa)
#define SEA_LEVEL_PRESSURE_PA  101325.0

// Low-pass filter smoothing coefficient for Accelerometer world frame
#define ACCEL_FILTER_ALPHA     0.25

// ======================== GLOBAL OBJECTS ========================
Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;

// ======================== KALMAN FILTER STRUCT ========================
struct Kalman {
  float q_angle;   // Process noise variance for accelerometer
  float q_bias;    // Process noise variance for gyro bias
  float r_measure; // Measurement noise variance
  float angle;     // Calculated angle
  float bias;      // Calculated gyro bias
  float p[2][2];   // Error covariance matrix
};

Kalman kalmanRoll;
Kalman kalmanPitch;

void initKalman(Kalman *k) {
  k->q_angle = 0.001f;
  k->q_bias = 0.003f;
  k->r_measure = 0.03f;
  k->angle = 0.0f;
  k->bias = 0.0f;
  k->p[0][0] = 0.0f;
  k->p[0][1] = 0.0f;
  k->p[1][0] = 0.0f;
  k->p[1][1] = 0.0f;
}

float kalmanUpdate(Kalman *k, float newAngle, float newRate, float dt) {
  // Predict
  float rate = newRate - k->bias;
  k->angle += dt * rate;

  k->p[0][0] += dt * (dt * k->p[1][1] - k->p[0][1] - k->p[1][0] + k->q_angle);
  k->p[0][1] -= dt * k->p[1][1];
  k->p[1][0] -= dt * k->p[1][1];
  k->p[1][1] += k->q_bias * dt;

  // Measurement Update (Kalman Gain)
  float s = k->p[0][0] + k->r_measure;
  float k0 = k->p[0][0] / s;
  float k1 = k->p[1][0] / s;

  float y = newAngle - k->angle;
  k->angle += k0 * y;
  k->bias += k1 * y;

  float p00_temp = k->p[0][0];
  float p01_temp = k->p[0][1];

  k->p[0][0] -= k0 * p00_temp;
  k->p[0][1] -= k0 * p01_temp;
  k->p[1][0] -= k1 * p00_temp;
  k->p[1][1] -= k1 * p01_temp;

  return k->angle;
}

// ======================== STATE VARIABLES ========================
unsigned long packetCount = 1;
unsigned long previousTime = 0;
unsigned long lastTxTime = 0;

float baseAltitude = 0.0;
bool isBaseAltitudeSet = false;

// Calibration Offsets
float gyroBiasX = 0, gyroBiasY = 0, gyroBiasZ = 0;
float accelBiasX = 0, accelBiasY = 0, accelBiasZ = 0;

// Filtered Orientation & World Acceleration
float roll = 0, pitch = 0, yaw = 0;
float filteredAX = 0, filteredAY = 0, filteredAZ = 0;

// Sensor Health Flags
bool bmpAvailable = false;
bool mpuAvailable = false;
bool loraAvailable = false;

// ======================== HELPER FUNCTIONS ========================

// Pad number with leading zeroes
String padNumber(unsigned long num, int digits) {
  String s = String(num);
  while (s.length() < digits) {
    s = "0" + s;
  }
  return s;
}

// Format timestamp as HH:MM:SS:MS
String getFormattedTime(unsigned long ms) {
  unsigned long hours = ms / 3600000;
  unsigned long minutes = (ms % 3600000) / 60000;
  unsigned long seconds = (ms % 60000) / 1000;
  unsigned long millisecs = ms % 1000;

  return padNumber(hours, 2) + ":" +
         padNumber(minutes, 2) + ":" +
         padNumber(seconds, 2) + ":" +
         padNumber(millisecs, 3);
}

// Calibrate IMU offsets on startup
void calibrateSensors() {
  Serial.println(F("[IMU] Calibrating MPU6050... Please keep CanSat upright and still."));
  const int SAMPLES = 200;
  float sumAX = 0, sumAY = 0, sumAZ = 0;
  float sumGX = 0, sumGY = 0, sumGZ = 0;

  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    sumAX += a.acceleration.x;
    sumAY += a.acceleration.y;
    sumAZ += a.acceleration.z - 9.80665f; // Expect 1g along Z axis when upright
    sumGX += g.gyro.x;
    sumGY += g.gyro.y;
    sumGZ += g.gyro.z;

    digitalWrite(PIN_LED_STATUS, (i % 10 < 5) ? HIGH : LOW);
    delay(10);
  }

  accelBiasX = sumAX / SAMPLES;
  accelBiasY = sumAY / SAMPLES;
  accelBiasZ = sumAZ / SAMPLES;

  gyroBiasX = sumGX / SAMPLES;
  gyroBiasY = sumGY / SAMPLES;
  gyroBiasZ = sumGZ / SAMPLES;

  digitalWrite(PIN_LED_STATUS, HIGH);
  Serial.println(F("[IMU] Calibration complete!"));
}

// ======================== SETUP ========================
void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(PIN_LED_STATUS, OUTPUT);
  digitalWrite(PIN_LED_STATUS, HIGH); // Mandatory power-on indicator LED

  Serial.println(F("\n=================================================="));
  Serial.println(F("🛰️  CanSat 2026 Flight Computer - Team Alpha (07)"));
  Serial.println(F("=================================================="));

  // 1. Initialize I2C Bus
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Wire.setClock(400000); // 400kHz Fast I2C

  // 2. Initialize BMP Sensor
  Serial.print(F("[BMP] Initializing Barometer... "));
  if (bmp.begin()) {
    bmpAvailable = true;
    Serial.println(F("SUCCESS (BMP180/085 detected)"));
  } else {
    Serial.println(F("FAILED! Check wiring. (Using fallback estimates)"));
  }

  // 3. Initialize MPU6050
  Serial.print(F("[IMU] Initializing MPU6050... "));
  if (mpu.begin()) {
    mpuAvailable = true;
    Serial.println(F("SUCCESS"));
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    calibrateSensors();

    initKalman(&kalmanRoll);
    initKalman(&kalmanPitch);

    // Initial orientation estimation
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float initRoll = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;
    float initPitch = atan(-a.acceleration.x / sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;

    kalmanRoll.angle = initRoll;
    kalmanPitch.angle = initPitch;
    roll = initRoll;
    pitch = initPitch;
  } else {
    Serial.println(F("FAILED! Check wiring."));
  }

  // 4. Initialize Altitude Baseline (Rule 2B: baseline must calibrate to 0m on ground)
  if (bmpAvailable) {
    Serial.print(F("[ALT] Calibrating Ground Baseline Altitude... "));
    float sumAlt = 0;
    for (int i = 0; i < 20; i++) {
      sumAlt += bmp.readAltitude(SEA_LEVEL_PRESSURE_PA);
      delay(25);
    }
    baseAltitude = sumAlt / 20.0;
    isBaseAltitudeSet = true;
    Serial.print(F("Ground Level Reference = "));
    Serial.print(baseAltitude, 2);
    Serial.println(F(" m"));
  }

  // 5. Initialize LoRa SX1278
  Serial.print(F("[RF]  Initializing SX1278 LoRa @ 433MHz... "));
  LoRa.setPins(PIN_LORA_SS, PIN_LORA_RST, PIN_LORA_DIO0);

  int loraRetries = 0;
  while (!LoRa.begin(LORA_FREQUENCY) && loraRetries < 5) {
    Serial.print(F("."));
    delay(400);
    loraRetries++;
  }

  if (loraRetries < 5) {
    loraAvailable = true;
    LoRa.setSyncWord(ACTIVE_SYNC_WORD);
    LoRa.setSpreadingFactor(7);           // SF7 for fast telemetry throughput
    LoRa.setSignalBandwidth(125E3);       // 125 kHz
    LoRa.setCodingRate4(5);               // 4/5 error coding
    LoRa.setTxPower(17);                  // 17 dBm (50mW output)
    Serial.println(F("SUCCESS"));
    Serial.print(F("      Sync Word configured to: 0x"));
    Serial.println(ACTIVE_SYNC_WORD, HEX);
  } else {
    Serial.println(F("FAILED! Continuing with Serial-only telemetry."));
  }

  previousTime = millis();
  Serial.println(F("[SYSTEM] Telemetry Loop Started (Ready for Drop/Launch)"));
  Serial.println(F("--------------------------------------------------\n"));
}

// ======================== MAIN LOOP ========================
void loop() {
  unsigned long currentTime = millis();
  float dt = (currentTime - previousTime) / 1000.0f;
  if (dt < 0.001f) dt = 0.001f;
  previousTime = currentTime;

  // ----------------- 1. SENSOR DATA ACQUISITION -----------------
  float pressurePa = 101325.0;
  float temperature = 25.0;
  float relativeAltitude = 0.0;

  if (bmpAvailable) {
    pressurePa = (float)bmp.readPressure();
    temperature = bmp.readTemperature();
    float rawAltitude = bmp.readAltitude(SEA_LEVEL_PRESSURE_PA);
    relativeAltitude = rawAltitude - baseAltitude;
    if (abs(relativeAltitude) < 0.05f) relativeAltitude = 0.0f; // clean ground floor zero
  }

  float accelWorldX = 0.0, accelWorldY = 0.0, accelWorldZ = 0.0;

  if (mpuAvailable) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Apply calibration offsets
    float calAX = a.acceleration.x - accelBiasX;
    float calAY = a.acceleration.y - accelBiasY;
    float calAZ = a.acceleration.z - accelBiasZ;

    float calGX = (g.gyro.x - gyroBiasX) * 180.0 / PI; // deg/s
    float calGY = (g.gyro.y - gyroBiasY) * 180.0 / PI;
    float calGZ = (g.gyro.z - gyroBiasZ) * 180.0 / PI;

    // Estimate Roll & Pitch from Accelerometer
    float accelRoll = atan2(calAY, calAZ) * 180.0 / PI;
    float accelPitch = atan(-calAX / sqrt(calAY * calAY + calAZ * calAZ)) * 180.0 / PI;

    // Kalman Filter updates
    roll = kalmanUpdate(&kalmanRoll, accelRoll, calGX, dt);
    pitch = kalmanUpdate(&kalmanPitch, accelPitch, calGY, dt);

    // Simple Yaw integration
    yaw += calGZ * dt;
    if (yaw > 180.0) yaw -= 360.0;
    if (yaw < -180.0) yaw += 360.0;

    // Low-pass filter for smooth acceleration profiles
    filteredAX = ACCEL_FILTER_ALPHA * calAX + (1.0 - ACCEL_FILTER_ALPHA) * filteredAX;
    filteredAY = ACCEL_FILTER_ALPHA * calAY + (1.0 - ACCEL_FILTER_ALPHA) * filteredAY;
    filteredAZ = ACCEL_FILTER_ALPHA * calAZ + (1.0 - ACCEL_FILTER_ALPHA) * filteredAZ;

    // World coordinate frame transformation (gravity-referenced)
    float rRad = roll * PI / 180.0;
    float pRad = pitch * PI / 180.0;
    float yRad = yaw * PI / 180.0;

    accelWorldX = filteredAX * cos(pRad) * cos(yRad) +
                  filteredAY * (sin(rRad) * sin(pRad) * cos(yRad) - cos(rRad) * sin(yRad)) +
                  filteredAZ * (cos(rRad) * sin(pRad) * cos(yRad) + sin(rRad) * sin(yRad));

    accelWorldY = filteredAX * cos(pRad) * sin(yRad) +
                  filteredAY * (sin(rRad) * sin(pRad) * sin(yRad) + cos(rRad) * cos(yRad)) +
                  filteredAZ * (cos(rRad) * sin(pRad) * sin(yRad) - sin(rRad) * cos(yRad));

    accelWorldZ = -filteredAX * sin(pRad) +
                   filteredAY * sin(rRad) * cos(pRad) +
                   filteredAZ * cos(rRad) * cos(pRad);

    // Dead-band noise threshold
    if (abs(accelWorldX) < 0.05) accelWorldX = 0.0;
    if (abs(accelWorldY) < 0.05) accelWorldY = 0.0;
    if (abs(accelWorldZ) < 0.05) accelWorldZ = 0.0;
  }

  // ----------------- 2. TELEMETRY TRANSMISSION -----------------
  // Target rate: ~2 packets per second (every 500 ms)
  if (currentTime - lastTxTime >= 500) {
    lastTxTime = currentTime;

    String timestampStr = getFormattedTime(currentTime);
    String packetNumStr = "P-" + padNumber(packetCount, 3);

    // Exact Mandatory Rulebook Format:
    // CAN-Team-XX; P-XXX; Ti-HH:MM:SS:MS; A-XXX.X; Pr-XXXX.XX; T-XX.X; Ro-XX.X; Pi-XX.X; Ya-XX.X; AX-XX.XX; AY-XX.XX; AZ-XX.XX;
    String telemetryPacket = TEAM_ID + "; " +
                             packetNumStr + "; " +
                             "Ti-" + timestampStr + "; " +
                             "A-"  + String(relativeAltitude, 1) + "; " +
                             "Pr-" + String(pressurePa, 2) + "; " +
                             "T-"  + String(temperature, 1) + "; " +
                             "Ro-" + String(roll, 1) + "; " +
                             "Pi-" + String(pitch, 1) + "; " +
                             "Ya-" + String(yaw, 1) + "; " +
                             "AX-" + String(accelWorldX, 2) + "; " +
                             "AY-" + String(accelWorldY, 2) + "; " +
                             "AZ-" + String(accelWorldZ, 2) + ";";

    // 1. Output to Serial (for debugging/bench test)
    Serial.println(telemetryPacket);

    // 2. Transmit over LoRa SX1278
    if (loraAvailable) {
      digitalWrite(PIN_LED_STATUS, LOW); // Flash LED during TX
      LoRa.beginPacket();
      LoRa.print(telemetryPacket);
      LoRa.endPacket();
      digitalWrite(PIN_LED_STATUS, HIGH);
    }

    packetCount++;
  }

  delay(10); // Small loop yield for RTOS scheduler
}\n