#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BMP280.h>

#define TEAM_NUMBER 21

// Status LED pin (mandatory indicator)
#define LED_PIN 4

// BMP280 sensor
Adafruit_BMP280 bmp;
#define I2C_SDA 21
#define I2C_SCL 22

// MPU6500 / MPU6050 registers
#define MPU_ADDR     0x68
#define PWR_MGMT_1   0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43
#define WHO_AM_I     0x75

// LoRa SPI pins
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2

// LoRa config
#define LORA_FREQUENCY 433E6
#define LORA_SF       7
#define LORA_BW       125E3
#define LORA_CR       5
#define LORA_SYNC     0xA5  // 0xA5 for launch, 0xF3 for testing

// Packet timing
unsigned long packetNumber = 0;
unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 500; // send every 500ms (2 Hz)

// Orientation and calibration variables
float roll = 0.0;
float pitch = 0.0;
float yaw = 0.0;
float gyroBiasX = 0.0, gyroBiasY = 0.0, gyroBiasZ = 0.0;
unsigned long lastImuTime = 0;

// Write single byte to MPU register
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// Read 16-bit signed integer from MPU register
int16_t read16(uint8_t reg) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)2);
  if (Wire.available() < 2) {
    return 0;
  }
  return (int16_t)((Wire.read() << 8) | Wire.read());
}

// Calibrate gyro offsets when device is at rest
void calibrateGyro() {
  Serial.print("Calibrating gyro offset... ");
  const int samples = 100;
  long gx = 0, gy = 0, gz = 0;

  for (int i = 0; i < samples; i++) {
    gx += read16(GYRO_XOUT_H);
    gy += read16(GYRO_XOUT_H + 2);
    gz += read16(GYRO_XOUT_H + 4);
    delay(10);
  }

  gyroBiasX = (gx / (float)samples) / 131.0;
  gyroBiasY = (gy / (float)samples) / 131.0;
  gyroBiasZ = (gz / (float)samples) / 131.0;
  Serial.println("done");
}

// Format timestamp string HH:MM:SS:MS
void getTime(unsigned long ms, char *buffer, size_t bufferSize) {
  unsigned long totalSeconds = ms / 1000;
  unsigned int milliseconds = ms % 1000;
  unsigned int seconds = totalSeconds % 60;
  unsigned int minutes = (totalSeconds / 60) % 60;
  unsigned int hours = (totalSeconds / 3600) % 24;

  snprintf(buffer, bufferSize, "%02u:%02u:%02u:%03u", hours, minutes, seconds, milliseconds);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // power indicator on

  Serial.println("\n--- CanSat Transmitter (Team 21) ---");

  // Init I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);

  // Init BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found at 0x76, trying 0x77...");
    if (!bmp.begin(0x77)) {
      Serial.println("BMP280 init failed!");
      while (1) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(200);
      }
    }
  }
  Serial.println("BMP280 connected");

  // Wake up MPU6500
  writeRegister(PWR_MGMT_1, 0x00);
  delay(100);

  // Check WHO_AM_I
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(WHO_AM_I);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)1);
  if (Wire.available()) {
    uint8_t whoAmI = Wire.read();
    Serial.print("MPU WHO_AM_I: 0x");
    Serial.println(whoAmI, HEX);
  } else {
    Serial.println("MPU not responding!");
  }

  calibrateGyro();

  // Initial angle estimation from accelerometer
  int16_t ax_init = read16(ACCEL_XOUT_H);
  int16_t ay_init = read16(ACCEL_XOUT_H + 2);
  int16_t az_init = read16(ACCEL_XOUT_H + 4);
  roll  = atan2((float)ay_init, (float)az_init) * 180.0 / PI;
  pitch = atan(-(float)ax_init / sqrt((float)ay_init * ay_init + (float)az_init * az_init)) * 180.0 / PI;
  lastImuTime = millis();

  // Init LoRa SPI
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  while (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("LoRa init failed, retrying...");
    delay(1000);
  }

  // Set LoRa parameters
  LoRa.setSpreadingFactor(LORA_SF);
  LoRa.setSignalBandwidth(LORA_BW);
  LoRa.setCodingRate4(LORA_CR);
  LoRa.setSyncWord(LORA_SYNC);
  LoRa.enableCrc();
  LoRa.setTxPower(17);

  Serial.println("LoRa transmitter ready");
  Serial.println("------------------------------------");
}

void loop() {
  unsigned long now = millis();

  // Update roll, pitch, yaw using complementary filter
  float dt = (now - lastImuTime) / 1000.0f;
  if (dt >= 0.01f) {
    lastImuTime = now;

    int16_t ax_raw = read16(ACCEL_XOUT_H);
    int16_t ay_raw = read16(ACCEL_XOUT_H + 2);
    int16_t az_raw = read16(ACCEL_XOUT_H + 4);
    int16_t gx_raw = read16(GYRO_XOUT_H);
    int16_t gy_raw = read16(GYRO_XOUT_H + 2);
    int16_t gz_raw = read16(GYRO_XOUT_H + 4);

    // Gyro rates in deg/s
    float gx = (gx_raw / 131.0) - gyroBiasX;
    float gy = (gy_raw / 131.0) - gyroBiasY;
    float gz = (gz_raw / 131.0) - gyroBiasZ;

    // Accel angles in degrees
    float accelRoll  = atan2((float)ay_raw, (float)az_raw) * 180.0 / PI;
    float accelPitch = atan(-(float)ax_raw / sqrt((float)ay_raw * ay_raw + (float)az_raw * az_raw)) * 180.0 / PI;

    // Filter fusion: 96% gyro + 4% accel
    roll  = 0.96f * (roll + gx * dt) + 0.04f * accelRoll;
    pitch = 0.96f * (pitch + gy * dt) + 0.04f * accelPitch;
    yaw  += gz * dt;
    if (yaw > 180.0f) yaw -= 360.0f;
    if (yaw < -180.0f) yaw += 360.0f;
  }

  // Send telemetry packet at fixed interval
  if (now - lastSend < SEND_INTERVAL) {
    return;
  }
  lastSend = now;
  packetNumber++;

  // Read barometric data (absolute sea-level altitude)
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(1013.25);

  // Convert raw acceleration to m/s^2 (1g = 9.80665 m/s^2)
  int16_t ax_raw = read16(ACCEL_XOUT_H);
  int16_t ay_raw = read16(ACCEL_XOUT_H + 2);
  int16_t az_raw = read16(ACCEL_XOUT_H + 4);
  float ax = (ax_raw / 16384.0f) * 9.80665f;
  float ay = (ay_raw / 16384.0f) * 9.80665f;
  float az = (az_raw / 16384.0f) * 9.80665f;

  // Generate timestamp
  char timeString[20];
  getTime(now, timeString, sizeof(timeString));

  // Team identifier
  char teamName[20];
  snprintf(teamName, sizeof(teamName), "CAN-Team-%02d", TEAM_NUMBER);

  // Format packet string per rulebook
  char packet[200];
  snprintf(
    packet,
    sizeof(packet),
    "%s; P-%03lu; Ti-%s; A-%.1f; Pr-%.2f; T-%.1f; Ro-%.1f; Pi-%.1f; Ya-%.1f; AX-%.2f; AY-%.2f; AZ-%.2f;",
    teamName,
    packetNumber,
    timeString,
    altitude,
    pressure,
    temperature,
    roll,
    pitch,
    yaw,
    ax,
    ay,
    az
  );

  // Print to serial monitor
  Serial.print("TX (");
  Serial.print(strlen(packet));
  Serial.print(" bytes): ");
  Serial.println(packet);

  // Transmit over LoRa (blink status LED)
  digitalWrite(LED_PIN, LOW);
  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();
  digitalWrite(LED_PIN, HIGH);
}
