/**
 * Standalone Test: LoRa SX1278 Transmitter
 * Pins: NSS=5, RST=14, DIO0=2, SCK=18, MISO=19, MOSI=23
 */
#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2

unsigned long counter = 1;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("--- Testing LoRa Transmitter (433MHz) ---"));

  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println(F("❌ LoRa init failed! Check SPI wiring and 3.3V power."));
    while (1) delay(100);
  }

  LoRa.setSyncWord(0xA5);
  Serial.println(F("✅ LoRa Transmitter ready!"));
}

void loop() {
  String msg = "CAN-Team-07; P-" + String(counter) + "; TEST PACKET";
  Serial.print(F("Sending: "));
  Serial.println(msg);

  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();

  counter++;
  delay(1000);
}\n