/**
 * Standalone Test: LoRa SX1278 Receiver
 * Pins: NSS=5, RST=14, DIO0=2, SCK=18, MISO=19, MOSI=23
 */
#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("--- Testing LoRa Receiver (433MHz) ---"));

  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println(F("❌ LoRa init failed! Check SPI wiring."));
    while (1) delay(100);
  }

  LoRa.setSyncWord(0xA5);
  Serial.println(F("✅ LoRa Receiver ready! Waiting for packets..."));
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print(F("Received: '"));
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.print(F("' | RSSI: "));
    Serial.println(LoRa.packetRssi());
  }
}\n