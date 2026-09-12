/**
 * ============================================================================
 * 📡 CanSat 2026 - Ground Station Receiver (Team 21 Gateway)
 * Target Board: ESP32 DevKit V1
 * Module: SX1278 LoRa 433 MHz (SPI)
 * ============================================================================
 */

#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2
#define LED_PIN    4

#define LORA_FREQUENCY 433E6
#define ACTIVE_SYNC_WORD 0xA5 // 0xA5 for launch, 0xF3 for testing

unsigned long totalPacketsReceived = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  Serial.println(F("============================================="));
  Serial.println(F("📡 CanSat Ground Station Receiver - CAN-Team-21"));
  Serial.println(F("============================================="));

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  Serial.print(F("Initializing LoRa Receiver @ 433 MHz... "));
  while (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.print(F("."));
    delay(500);
  }

  LoRa.setSyncWord(ACTIVE_SYNC_WORD);
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();

  Serial.println(F("SUCCESS!"));
  Serial.println(F("Listening for incoming CanSat telemetry packets...\n"));
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    digitalWrite(LED_PIN, LOW); // Flash LED on packet receipt

    String rawPacket = "";
    while (LoRa.available()) {
      rawPacket += (char)LoRa.read();
    }

    int rssi = LoRa.packetRssi();
    float snr = LoRa.packetSnr();
    totalPacketsReceived++;

    // Print raw packet to Serial for Web Dashboard parsing
    Serial.println(rawPacket);

    digitalWrite(LED_PIN, HIGH);
  }
}
