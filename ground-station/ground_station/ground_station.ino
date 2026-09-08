/**
 * ============================================================================
 * 📡 CanSat 2026 - Ground Station Receiver (Practice & Local Testing)
 * Team Name: Team Alpha (CAN-Team-07)
 * Target Board: ESP32 DevKit V1
 * Module: SX1278 LoRa 433 MHz (SPI)
 * ============================================================================
 * 
 * Functions:
 * 1. Receives 433 MHz LoRa packets transmitted by CanSat.
 * 2. Formats packets with RSSI and sends to Serial for the Web Dashboard.
 * 3. Sync Word: 0xA5 (Launch) / 0xF3 (Testing)
 * ============================================================================
 */

#include <SPI.h>
#include <LoRa.h>

// Pin Definitions for ESP32
#define PIN_LORA_SS   5
#define PIN_LORA_RST  14
#define PIN_LORA_DIO0 2
#define PIN_LED       4

#define LORA_FREQUENCY 433E6
#define ACTIVE_SYNC_WORD 0xA5 // Match CanSat sync word

unsigned long totalPacketsReceived = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  Serial.println(F("============================================="));
  Serial.println(F("📡 CanSat Ground Station Receiver - Team Alpha"));
  Serial.println(F("============================================="));

  LoRa.setPins(PIN_LORA_SS, PIN_LORA_RST, PIN_LORA_DIO0);

  Serial.print(F("Initializing LoRa Receiver @ 433 MHz... "));
  while (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.print(F("."));
    delay(500);
  }

  LoRa.setSyncWord(ACTIVE_SYNC_WORD);
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println(F("SUCCESS!"));
  Serial.println(F("Listening for incoming CanSat telemetry packets...\n"));
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    digitalWrite(PIN_LED, LOW); // Flash on receive

    String rawPacket = "";
    while (LoRa.available()) {
      rawPacket += (char)LoRa.read();
    }

    int rssi = LoRa.packetRssi();
    float snr = LoRa.packetSnr();

    totalPacketsReceived++;

    // Print to Serial for Web Dashboard parsing
    Serial.print(rawPacket);
    Serial.print(F(" [RSSI: "));
    Serial.print(rssi);
    Serial.print(F(" dBm, SNR: "));
    Serial.print(snr, 1);
    Serial.println(F(" dB]"));

    digitalWrite(PIN_LED, HIGH);
  }
}\n