/**
 * Standalone Test: MPU6050 6-Axis IMU
 * Connect: SDA -> GPIO 21, SCL -> GPIO 22, VCC -> 3.3V, GND -> GND
 */
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("--- Testing MPU6050 IMU ---"));

  Wire.begin(21, 22);

  if (!mpu.begin()) {
    Serial.println(F("❌ MPU6050 not detected! Check SDA=21, SCL=22."));
    while (1) delay(100);
  }

  Serial.println(F("✅ MPU6050 Found!"));
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float roll = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;
  float pitch = atan(-a.acceleration.x / sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;

  Serial.print(F("Accel (m/s^2) -> X: "));
  Serial.print(a.acceleration.x, 2);
  Serial.print(F(" Y: "));
  Serial.print(a.acceleration.y, 2);
  Serial.print(F(" Z: "));
  Serial.print(a.acceleration.z, 2);
  Serial.print(F(" | Angles -> Roll: "));
  Serial.print(roll, 1);
  Serial.print(F("° Pitch: "));
  Serial.print(pitch, 1);
  Serial.println(F("°"));

  delay(300);
}\n