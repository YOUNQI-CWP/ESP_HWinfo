#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

#define SERIAL_BAUD_RATE       115200
#define SERIAL_INIT_DELAY      1000
#define WIFI_INIT_DELAY_MS     500
#define BLE_INIT_DELAY_MS      500
#define BLE_DEVICE_NAME        "ESP32-Info"

// ==================== 芯片能力标记 ====================
// ESP8266 系列
#if defined(ESP8266)
    #define HAS_WIFI        1
    #define HAS_BLE         0
    #define HAS_PSRAM       0
    #define HAS_DUAL_CORE   0
    #define HAS_VCC         1

// ESP32 系列
#elif CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2 || \
      CONFIG_IDF_TARGET_ESP32S3 || CONFIG_IDF_TARGET_ESP32C3
    #define HAS_WIFI        1
    #if !CONFIG_IDF_TARGET_ESP32S2
        #define HAS_BLE     1
    #else
        #define HAS_BLE     0
    #endif
    #if defined(BOARD_HAS_PSRAM) || defined(CONFIG_SPIRAM)
        #define HAS_PSRAM   1
    #else
        #define HAS_PSRAM   0
    #endif
    #define HAS_DUAL_CORE   1
    #define HAS_VCC         0

#else
    #define HAS_WIFI        0
    #define HAS_BLE         0
    #define HAS_PSRAM       0
    #define HAS_DUAL_CORE   0
    #define HAS_VCC         0
#endif

#endif
