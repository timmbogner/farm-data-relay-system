//  FARM DATA RELAY SYSTEM
//
//  GATEWAY 2.000
//
//  Developed by Timm Bogner (timmbogner@gmail.com) for Sola Gratia Farm in Urbana, Illinois, USA.
//

#define CREDENTIALS 
#define DEBUG

#define ROLE ESPNOW_GATEWAY

#include <FDRSdefaults.h>
#include "fdrs_config.h"
#include "DataReading.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <espnow.h>
#elif defined(ESP32)
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#endif
#include <ArduinoJson.h>
#ifdef USE_WIFI
#include <PubSubClient.h>
#endif
#ifdef USE_LORA
#include <LoRa.h>
#endif
#ifdef USE_LED
#include <FastLED.h>
#endif
#include "fdrs_functions.h"

void setup() {
#if defined(ESP8266)
  UART_IF.begin(115200);
#elif defined(ESP32)
  Serial.begin(115200);
  UART_IF.begin(115200, SERIAL_8N1, RXD2, TXD2);
#endif
  DBG("Initializing FDRS Gateway");
  DBG("Address:" + String (UNIT_MAC, HEX));
#ifdef USE_LED
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  leds[0] = CRGB::Blue;
  FastLED.show();
#endif
#ifdef USE_WIFI
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    DBG("Connecting to Wifi...");
    delay(500);
  }
  client.setServer(mqtt_server, 1883);
  if (!client.connected()) {
    DBG("Connecting mqtt...");
    reconnect();
  }
  client.setCallback(mqtt_callback);
#else
  begin_espnow();
#endif
#ifdef USE_LORA
  DBG("Initializing LoRa!");
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    while (1);
  }
  DBG(" LoRa initialized.");
#endif
  //  UART_IF.println(sizeof(DataReading));

}

void loop() {
  if (millis() > timeESPNOWG) {
    timeESPNOWG += ESPNOWG_DELAY;
    if  (lenESPNOWG > 0) releaseESPNOW(0);
  }
  if (millis() > timeESPNOW1) {
    timeESPNOW1 += ESPNOW1_DELAY;
    if (lenESPNOW1 > 0)   releaseESPNOW(1);
  }
  if (millis() > timeESPNOW2) {
    timeESPNOW2 += ESPNOW2_DELAY;
    if (lenESPNOW2 > 0) releaseESPNOW(2);
  }
  if (millis() > timeSERIAL) {
    timeSERIAL  += SERIAL_DELAY;
    if (lenSERIAL  > 0) releaseSerial();
  }
  if (millis() > timeMQTT) {
    timeMQTT += MQTT_DELAY;
    if (lenMQTT    > 0) releaseMQTT();
  }
  if (millis() > timeLORAG) {
    timeLORAG += LORAG_DELAY;
    if (lenLORAG    > 0) releaseLoRa(0);
  }
  if (millis() > timeLORA1) {
    timeLORA1 += LORA1_DELAY;
    if (lenLORA1    > 0) releaseLoRa(1);
  }
  if (millis() > timeLORA2) {
    timeLORA2 += LORA2_DELAY;
    if (lenLORA2    > 0) releaseLoRa(2);
  }

  while (UART_IF.available()) {
    getSerial();
  }
  getLoRa();
#ifdef USE_WIFI
  if (!client.connected()) {
    Serial.println("Connecting mqtt...");
    reconnect();
  }
  client.loop();
#endif
  if (newData) {
    switch (newData) {
      case 1:     //ESP-NOW #1
        ESPNOW1_ACT
        break;
      case 2:     //ESP-NOW #2
        ESPNOW2_ACT
        break;
      case 3:     //ESP-NOW General
        ESPNOWG_ACT
        break;
      case 4:     //Serial
        SERIAL_ACT
        break;
      case 5:     //MQTT
        MQTT_ACT
        break;
      case 6:     //LoRa General
        LORAG_ACT
        break;
      case 7:     //LoRa #1
        LORA1_ACT
        break;
      case 8:     //LoRa #2
        LORA2_ACT
        break;
    }
    newData = 0;
  }
}