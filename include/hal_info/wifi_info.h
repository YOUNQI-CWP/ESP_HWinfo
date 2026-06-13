#ifndef WIFI_INFO_H
#define WIFI_INFO_H

#include <Arduino.h>

struct WifiInfo {
    uint8_t mode;
    const char* mac;
    const char* hostname;
    uint8_t txPower;
    uint8_t channel;
    uint8_t secondChan;
    uint8_t protocol;
    char countryCode[4];
    uint16_t inactiveTime;
    bool connected;
    const char* ssid;
    const char* bssid;
    int8_t rssi;
    const char* authMode;
    uint8_t apChannel;
    int8_t apRssi;
    const char* apMac;
    const char* apIP;
    const char* apSsid;
    uint8_t apClients;
};

void wifiInfoInit(WifiInfo& info);
void wifiInfoPrint(const WifiInfo& info);

#endif
