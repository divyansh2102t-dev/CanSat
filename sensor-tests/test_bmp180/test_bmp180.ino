/**
 * Standalone Test: BMP180 / BMP085 Barometer
 * Connect: SDA -> GPIO 21, SCL -> GPIO 22, VCC -> 3.3V, GND -> GND
 */
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
float baseAltitude = 0.0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("--- Testing BMP180 Barometer ---"));

  Wire.begin(21, 22);

  if (!bmp.begin()) {
    Serial.println(F("❌ BMP180 not detected! Check SDA=21, SCL=22, 3.3V power."));
    while (1) delay(100);
  }

  Serial.println(F("✅ BMP180 Found!"));
  
  // Calibrate base
  float sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += bmp.readAltitude(101325.0);
    delay(30);
  }
  baseAltitude = sum / 20.0;
  Serial.print(F("Base Altitude Calibrated: "));
  Serial.print(baseAltitude);
  Serial.println(F(" m\n"));
}

void loop() {
  float temp = bmp.readTemperature();
  int32_t pressure = bmp.readPressure();
  float rawAlt = bmp.readAltitude(101325.0);
  float relAlt = rawAlt - baseAltitude;

  Serial.print(F("Temp: "));
  Serial.print(temp, 1);
  Serial.print(F(" °C | Pressure: "));
  Serial.print(pressure);
  Serial.print(F(" Pa | Rel Alt: "));
  Serial.print(relAlt, 2);
  Serial.println(F(" m"));

  delay(500);
}\n