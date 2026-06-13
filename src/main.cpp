#include <Arduino.h>
#include "config/hardware_config.h"
#include "hardware_info.h"

#if HAS_WIFI
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#endif

#if HAS_BLE
#include <BLEDevice.h>
#endif

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(SERIAL_INIT_DELAY);

#if HAS_WIFI
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    delay(WIFI_INIT_DELAY_MS);
#endif

#if HAS_BLE
    BLEDevice::init(BLE_DEVICE_NAME);
    delay(BLE_INIT_DELAY_MS);
#endif

    hwInfo().init();
    hwInfo().printAll();
}

void loop() {
    delay(10000);
}
